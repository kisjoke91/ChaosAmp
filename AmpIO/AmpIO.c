#include "AmpIO.h"
#include "main.h"
#include "ILI9341_STM32_Driver.h"
#include "GUI.h"

extern I2C_HandleTypeDef AMPIO_TEMP_HI2C_INSTANCE;
extern I2C_HandleTypeDef AMPIO_MEM_HI2C_INSTANCE;
extern uint8_t checkInputs;
extern uint8_t signalDetected;

uint8_t status;
uint8_t ampIsOn = 0;
int16_t tempLeft;
int16_t tempRight;
int32_t shutdownTimer;
AmpIO_settings settings;

void AmpIO_loop(void) {

    AmpIO_Button b = AmpIO_getButton();

    if (b == AMPIO_POWER) {

        ampIsOn ^= 1;
        if (ampIsOn) {
            AmpIO_turnOn();
        }
        else if (GUI_deinit()) AmpIO_turnOff();
        else ampIsOn = 1;
    }

    if (ampIsOn) {

        AmpIO_statusMonitoring();
        GUI_loop(b);
    }
}

void AmpIO_statusMonitoring(void) {

    if (!checkInputs) return;

    // Hold errors until power off
    status = (status & ((1 << AMPIO_STATUS_DC) |
                        (1 << AMPIO_STATUS_OVERHEATED) |
                        (1 << AMPIO_STATUS_EEPROM)));

    // Check fuses
    if ((!HAL_GPIO_ReadPin(FUSE_R_GPIO_Port, FUSE_R_Pin)) ||
        (!HAL_GPIO_ReadPin(FUSE_R_GPIO_Port, FUSE_R_Pin))) {

        // The fuses will be only checked if the transformer is on
        if (HAL_GPIO_ReadPin(T_OUT_GPIO_Port, T_OUT_Pin)) {

            status |= (1 << AMPIO_STATUS_FUSES);
            AmpIO_fuseErrorHandler();
        }
    }

    // Check for signal
    if (signalDetected ||
        !HAL_GPIO_ReadPin(SIGNAL_IN_GPIO_Port, SIGNAL_IN_Pin)) {

        // Reset shutdown timer
        AmpIO_resetShutdownTimer();
        signalDetected = 0;
    }

    else {
        if (shutdownTimer < settings.shutdownTimeout * 60) {
            status |= (1 << AMPIO_STATUS_TIMER);
        }
        AmpIO_noSignalHandler();
    }

    // Check temperature
    tempLeft = AmpIO_readTemperature(AMPIO_TEMP_CH_L_ADDRESS);
    tempRight = AmpIO_readTemperature(AMPIO_TEMP_CH_R_ADDRESS);

    if (tempLeft >= settings.switchOffTemperature ||
        tempRight >= settings.switchOffTemperature ) {

        status |= (1 << AMPIO_STATUS_OVERHEATED);
        AmpIO_overtemperatureHandler();
    }

    else if (tempLeft >= settings.warningTemperature ||
        tempRight >= settings.warningTemperature) {

        status |= (1 << AMPIO_STATUS_TEMP_WARNING);
        AmpIO_highTemperatureHandler();
    }

    // Check for no errors
    if (!(status & 0xFF)) {

        status = (1 << AMPIO_STATUS_OK);
        AmpIO_statusOKHandler();
    }

    checkInputs = 0;
}

void AmpIO_statusOKHandler(void) {

}

void AmpIO_overtemperatureHandler(void) {

    AmpIO_transformerOff();
    AmpIO_disableSpeakers();
}

void AmpIO_highTemperatureHandler(void) {

}

void AmpIO_fuseErrorHandler(void) {

}

void AmpIO_dcErrorHandler(void) {

    if (settings.dcProtectionEnabled) {

        status |= (1 << AMPIO_STATUS_DC);
        AmpIO_transformerOff();
        AmpIO_disableSpeakers();
    }
}

void AmpIO_noSignalHandler(void) {

    if (settings.shutdownTimerEnabled) shutdownTimer --;
    else AmpIO_resetShutdownTimer();

    if (shutdownTimer < 1)
        AmpIO_turnOff();
}

void AmpIO_resetShutdownTimer(void) {

    shutdownTimer = settings.shutdownTimeout * 60;
    shutdownTimer += AMPIO_WAIT_BEFORE_COUNTDOWN;
}

void AmpIO_turnOn(void) {

    status = 0; // reset previous errors
    uint8_t error;

    AmpIO_loadParameter(&error);

    if (error != HAL_OK) {
        AmpIO_loadDefaultParameterOnError();
        status |= (1 << AMPIO_STATUS_EEPROM);
    }

    else if (settings.configured != AMPIO_MEM_IS_CONFIGURED) {
        AmpIO_writeDefaultParameter();
        AmpIO_loadParameter(NULL);
    }

    // initialize shutdownTimer variable
    AmpIO_resetShutdownTimer();

    // Check the status of the amplifier
    // Check for errors before turning transformer on
    checkInputs = 1; // required by statusMonitoring
    AmpIO_statusMonitoring();

    // if the amplifier is not overheated, turn
    // transformer on
    if (!(status & (1 << AMPIO_STATUS_OVERHEATED))) {
        AmpIO_transformerOn();
        HAL_Delay(100);
    }

    GUI_init();
    ILI9341_LED_On();

    if (settings.clipProtectionEnabled)
        HAL_Delay(settings.clipDelayAfterStart * 1000);

    AmpIO_enableSpeakers();
    GUI_ShowStatus(1);
}

void AmpIO_turnOff(void) {

    AmpIO_transformerOff();
    AmpIO_disableSpeakers();

    ILI9341_LED_Off();
    ILI9341_Fill_Screen(BLACK);
    ampIsOn = 0;
}

AmpIO_Button AmpIO_getButton(void) {

    static AmpIO_Button lastPressed = AMPIO_NOPE;
    static uint32_t lastPressedTime;
    AmpIO_Button current = AMPIO_NOPE;

    if (!HAL_GPIO_ReadPin(B_ESC_GPIO_Port, B_ESC_Pin)) current = AMPIO_ESC;
    else if (!HAL_GPIO_ReadPin(B_UP_GPIO_Port, B_UP_Pin)) current = AMPIO_UP;
    else if (!HAL_GPIO_ReadPin(B_DOWN_GPIO_Port, B_DOWN_Pin)) current = AMPIO_DOWN;
    else if (!HAL_GPIO_ReadPin(B_ENTER_GPIO_Port, B_ENTER_Pin)) current = AMPIO_ENTER;
    else if (!HAL_GPIO_ReadPin(B_PWR_GPIO_Port, B_PWR_Pin)) current = AMPIO_POWER;

    if (lastPressed == AMPIO_NOPE && current != AMPIO_NOPE) {
        lastPressed = current;
        lastPressedTime = HAL_GetTick();
        HAL_Delay(20);

        if (settings.shutdownResetEnabled)
            AmpIO_resetShutdownTimer();

        return current;
    }

    if (lastPressed != AMPIO_NOPE && current == AMPIO_NOPE) {
        HAL_Delay(20);
        lastPressed = AMPIO_NOPE;
    }

    if (lastPressed != AMPIO_NOPE &&
        current == lastPressed &&
        (current == AMPIO_UP || current == AMPIO_DOWN)) {
        if (lastPressedTime + 1000 < HAL_GetTick()) {

            if (HAL_GetTick() - lastPressedTime < 4000) HAL_Delay(100);
            else HAL_Delay(50);
            return current;
        }
    }

    return AMPIO_NOPE;
}

void AmpIO_transformerOn(void) {
    HAL_GPIO_WritePin(T_OUT_GPIO_Port, T_OUT_Pin, GPIO_PIN_SET);
}

void AmpIO_transformerOff(void) {
    HAL_GPIO_WritePin(T_OUT_GPIO_Port, T_OUT_Pin, GPIO_PIN_RESET);
}

void AmpIO_enableSpeakers(void) {
    HAL_GPIO_WritePin(L_OUT_GPIO_Port, L_OUT_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(R_OUT_GPIO_Port, R_OUT_Pin, GPIO_PIN_SET);
}

void AmpIO_disableSpeakers(void) {
    HAL_GPIO_WritePin(L_OUT_GPIO_Port, L_OUT_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(R_OUT_GPIO_Port, R_OUT_Pin, GPIO_PIN_RESET);
}

int16_t AmpIO_readTemperature(uint16_t channel) {

    uint8_t cmd[2];

    HAL_I2C_Master_Receive (AMPIO_TEMP_HI2C_INSTANCE_PTR, channel, cmd, 2, 1);

    // Calculate temperature value in Celcius
    int16_t i16 = (cmd[0] << 8) | cmd[1];
    return i16 / 256.0;
}

void AmpIO_writeParameter(uint8_t address, uint8_t data) {

    uint8_t cmd[3];
    cmd[0] = 0;
    cmd[1] = address;
    cmd[2] = data;

    HAL_I2C_Master_Transmit(AMPIO_MEM_HI2C_INSTANCE_PTR,
                            AMPIO_MEM_ADDRESS, cmd, 3, 10);

    HAL_Delay(5);
}

uint8_t AmpIO_readParameter(uint8_t address, uint8_t * error) {

    uint8_t data;
    uint8_t err;
    uint8_t cmd[2];
    cmd[0] = 0;
    cmd[1] = address;

    HAL_I2C_Master_Transmit(AMPIO_MEM_HI2C_INSTANCE_PTR,
                            AMPIO_MEM_ADDRESS, cmd, 2, 10);

    err = HAL_I2C_Master_Receive(AMPIO_MEM_HI2C_INSTANCE_PTR,
                           AMPIO_MEM_ADDRESS, (uint8_t *) &data, 1, 10);
    HAL_Delay(10);

    if (error)
        *error = err;
    return data;
}

void AmpIO_loadParameter(uint8_t * error) {

    settings.clipProtectionEnabled =
        AmpIO_readParameter(AMPIO_MEM_ADDR_CLIP_EN, NULL);

    settings.clipDelayAfterStart =
        AmpIO_readParameter(AMPIO_MEM_ADDR_CLIP_DELAY, NULL);

    settings.switchOffTemperature =
        AmpIO_readParameter(AMPIO_MEM_ADDR_OFF_TEMP, NULL);

    settings.warningTemperature =
        AmpIO_readParameter(AMPIO_MEM_ADDR_WARNING_TEMP, NULL);

    settings.shutdownTimerEnabled =
        AmpIO_readParameter(AMPIO_MEM_ADDR_TIMER_EN, NULL);

    settings.shutdownResetEnabled =
        AmpIO_readParameter(AMPIO_MEM_ADDR_TIMER_RESET_EN, NULL);

    settings.shutdownTimeout =
        AmpIO_readParameter(AMPIO_MEM_ADDR_TIMEOUT, NULL);

    settings.dcProtectionEnabled =
        AmpIO_readParameter(AMPIO_MEM_ADDR_DC_EN, NULL);

    settings.language =
        AmpIO_readParameter(AMPIO_MEM_ADDR_LANGUAGE, NULL);

    settings.configured =
        AmpIO_readParameter(AMPIO_MEM_ADDR_CONFIG_CHECK, error);
}

void AmpIO_writeDefaultParameter(void) {

    AmpIO_writeParameter(AMPIO_MEM_ADDR_CLIP_EN, 1);
    AmpIO_writeParameter(AMPIO_MEM_ADDR_CLIP_DELAY, 3); // seconds
    AmpIO_writeParameter(AMPIO_MEM_ADDR_OFF_TEMP, 85); //°C
    AmpIO_writeParameter(AMPIO_MEM_ADDR_WARNING_TEMP, 75); // °C
    AmpIO_writeParameter(AMPIO_MEM_ADDR_TIMER_EN, 1);
    AmpIO_writeParameter(AMPIO_MEM_ADDR_TIMER_RESET_EN, 1);
    AmpIO_writeParameter(AMPIO_MEM_ADDR_TIMEOUT, 5); // minutes
    AmpIO_writeParameter(AMPIO_MEM_ADDR_DC_EN, 1);
    AmpIO_writeParameter(AMPIO_MEM_ADDR_LANGUAGE, GUI_LANG_EN);
    AmpIO_writeParameter(AMPIO_MEM_ADDR_CONFIG_CHECK,
                         AMPIO_MEM_IS_CONFIGURED);
}

void AmpIO_loadDefaultParameterOnError(void) {

    settings.clipProtectionEnabled = 1;
    settings.clipDelayAfterStart = 3;
    settings.switchOffTemperature = 85;
    settings.warningTemperature = 75;
    settings.shutdownTimerEnabled = 1;
    settings.shutdownResetEnabled = 1;
    settings.shutdownTimeout = 5;
    settings.dcProtectionEnabled = 1;
    settings.language = GUI_LANG_EN;
}
