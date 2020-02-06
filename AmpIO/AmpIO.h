#ifndef __AMPIO_H__
#define __AMPIO_H__

#include <inttypes.h>

#define AMPIO_STATUS_OK                           0
#define AMPIO_STATUS_TEMP_WARNING                 1
#define AMPIO_STATUS_OVERHEATED                   2
#define AMPIO_STATUS_DC                           3
#define AMPIO_STATUS_FUSES                        4
#define AMPIO_STATUS_TIMER                        5
#define AMPIO_STATUS_EEPROM                       6
#define AMPIO_STATUS_UNDEFINED                    7

#define AMPIO_TEMP_CH_L_ADDRESS                   0x48 << 1
#define AMPIO_TEMP_CH_R_ADDRESS                   0x49 << 1
#define AMPIO_MEM_ADDRESS                         0x50 << 1
#define AMPIO_TEMP_HI2C_INSTANCE                  hi2c1
#define AMPIO_TEMP_HI2C_INSTANCE_PTR              &hi2c1
#define AMPIO_MEM_HI2C_INSTANCE                   hi2c2
#define AMPIO_MEM_HI2C_INSTANCE_PTR               &hi2c2

//unit in secons
#define AMPIO_WAIT_BEFORE_COUNTDOWN               25

#define AMPIO_MEM_IS_CONFIGURED                   42U
#define AMPIO_MEM_ADDR_CLIP_EN                    0
#define AMPIO_MEM_ADDR_CLIP_DELAY                 1
#define AMPIO_MEM_ADDR_OFF_TEMP                   2
#define AMPIO_MEM_ADDR_WARNING_TEMP               3
#define AMPIO_MEM_ADDR_TIMER_EN                   4
#define AMPIO_MEM_ADDR_TIMER_RESET_EN             5
#define AMPIO_MEM_ADDR_TIMEOUT                    6
#define AMPIO_MEM_ADDR_DC_EN                      7
#define AMPIO_MEM_ADDR_LANGUAGE                   8
#define AMPIO_MEM_ADDR_CONFIG_CHECK               9


typedef enum AmpIO_Button
{
    AMPIO_NOPE,
    AMPIO_ESC,
    AMPIO_UP,
    AMPIO_DOWN,
    AMPIO_ENTER,
    AMPIO_POWER
} AmpIO_Button;

typedef struct {
    uint8_t clipProtectionEnabled;
    uint8_t clipDelayAfterStart; // seconds
    uint8_t switchOffTemperature; // °C
    uint8_t warningTemperature; // °C
    uint8_t shutdownTimerEnabled;
    uint8_t shutdownResetEnabled;
    uint8_t shutdownTimeout; // minutes
    uint8_t dcProtectionEnabled;
    uint8_t language;
    uint8_t configured;
} AmpIO_settings;



void AmpIO_loop(void);
void AmpIO_turnOn(void);
void AmpIO_turnOff(void);
AmpIO_Button AmpIO_getButton(void);
void AmpIO_transformerOn(void);
void AmpIO_transformerOff(void);
void AmpIO_enableSpeakers(void);
void AmpIO_disableSpeakers(void);
int16_t AmpIO_readTemperature(uint16_t channel);
void AmpIO_resetShutdownTimer(void);
void AmpIO_writeParameter(uint8_t address, uint8_t data);
uint8_t AmpIO_readParameter(uint8_t address, uint8_t * error);
void AmpIO_loadParameter(uint8_t * error);
void AmpIO_writeDefaultParameter(void);
void AmpIO_loadDefaultParameterOnError(void);

// status handler functions
void AmpIO_statusMonitoring(void);
void AmpIO_statusOKHandler(void);
void AmpIO_overtemperatureHandler(void);
void AmpIO_highTemperatureHandler(void);
void AmpIO_fuseErrorHandler(void);
void AmpIO_dcErrorHandler(void);
void AmpIO_noSignalHandler(void);

#endif /* __AMPIO_H__ */
