#include "GUI.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "Tahoma12.h"
#include "Tahoma32.h"
#include "Tahoma14.h"
#include <stdio.h>
#include <string.h>

// VARIABLES

extern uint8_t refreshUIStatus;
extern uint8_t refreshUITemperature;
extern uint8_t status;
extern uint8_t tempLeft, tempRight;
extern uint32_t shutdownTimer;
extern AmpIO_settings settings;

uint8_t selected;
uint8_t menuActive;
uint8_t submenuActive;
uint8_t drawInputText = 0;

const uint16_t cursorPos[] = {
    GUI_MENU_CURSOR_POS_0,
    GUI_MENU_CURSOR_POS_1,
    GUI_MENU_CURSOR_POS_2,
    GUI_MENU_CURSOR_POS_3,
    GUI_MENU_CURSOR_POS_4,
    GUI_MENU_CURSOR_POS_5
};
const uint16_t textPos[] = {
    GUI_MENU_TEXT_POS_0,
    GUI_MENU_TEXT_POS_1,
    GUI_MENU_TEXT_POS_2,
    GUI_MENU_TEXT_POS_3,
    GUI_MENU_TEXT_POS_4,
    GUI_MENU_TEXT_POS_5
};

const char en_labels[26][32] = {
    GUI_LABEL_EN_ON,
    GUI_LABEL_EN_OFF,
    GUI_LABEL_EN_CLIP_PROTECTION,
    GUI_LABEL_EN_DELAY,
    GUI_LABEL_EN_SHUTDOWN_TIMER,
    GUI_LABEL_EN_IDLE_TIME,
    GUI_LABEL_EN_RESET_ON_KEYPRESS,
    GUI_LABEL_EN_DC_PROTECTION,
    GUI_LABEL_EN_OVERHEAT_PROTECTION,
    GUI_LABEL_EN_CRITICAL_TEMPRATURE,
    GUI_LABEL_EN_WARNING_TEMPRATURE,
    GUI_LABEL_EN_INFO,
    GUI_LABEL_EN_FW_VERSION,
    GUI_LABEL_EN_MANUFACTURE_YEAR,
    GUI_LABEL_EN_LANGUAGE,
    GUI_LABEL_EN_LANGUAGE_2,
    GUI_LABEL_EN_AMPLIFIER_IS_ACTIVE,
    GUI_LABEL_EN_OVERTEMPERATURE,
    GUI_LABEL_EN_TEMPERATURE_WARNING,
    GUI_LABEL_EN_DC_VOLTAGE_DETECTED,
    GUI_LABEL_EN_CHECK_FUSES,
    GUI_LABEL_EN_NO_SIGNAL,
    GUI_LABEL_EN_STARTING_AMPLIFIER,
    GUI_LABEL_EN_ENABLE,
    GUI_LABEL_EN_EEPROM_ERROR,
    GUI_LABEL_EN_INPUT_MONITOR
};

const char hu_labels[26][32] = {
    GUI_LABEL_HU_ON,
    GUI_LABEL_HU_OFF,
    GUI_LABEL_HU_CLIP_PROTECTION,
    GUI_LABEL_HU_DELAY,
    GUI_LABEL_HU_SHUTDOWN_TIMER,
    GUI_LABEL_HU_IDLE_TIME,
    GUI_LABEL_HU_RESET_ON_KEYPRESS,
    GUI_LABEL_HU_DC_PROTECTION,
    GUI_LABEL_HU_OVERHEAT_PROTECTION,
    GUI_LABEL_HU_CRITICAL_TEMPRATURE,
    GUI_LABEL_HU_WARNING_TEMPRATURE,
    GUI_LABEL_HU_INFO,
    GUI_LABEL_HU_FW_VERSION,
    GUI_LABEL_HU_MANUFACTURE_YEAR,
    GUI_LABEL_HU_LANGUAGE,
    GUI_LABEL_HU_LANGUAGE_2,
    GUI_LABEL_HU_AMPLIFIER_IS_ACTIVE,
    GUI_LABEL_HU_OVERTEMPERATURE,
    GUI_LABEL_HU_TEMPERATURE_WARNING,
    GUI_LABEL_HU_DC_VOLTAGE_DETECTED,
    GUI_LABEL_HU_CHECK_FUSES,
    GUI_LABEL_HU_NO_SIGNAL,
    GUI_LABEL_HU_STARTING_AMPLIFIER,
    GUI_LABEL_HU_ENABLE,
    GUI_LABEL_HU_EEPROM_ERROR,
    GUI_LABEL_HU_INPUT_MONITOR
};

const char de_labels[26][32] = {
    GUI_LABEL_DE_ON,
    GUI_LABEL_DE_OFF,
    GUI_LABEL_DE_CLIP_PROTECTION,
    GUI_LABEL_DE_DELAY,
    GUI_LABEL_DE_SHUTDOWN_TIMER,
    GUI_LABEL_DE_IDLE_TIME,
    GUI_LABEL_DE_RESET_ON_KEYPRESS,
    GUI_LABEL_DE_DC_PROTECTION,
    GUI_LABEL_DE_OVERHEAT_PROTECTION,
    GUI_LABEL_DE_CRITICAL_TEMPRATURE,
    GUI_LABEL_DE_WARNING_TEMPRATURE,
    GUI_LABEL_DE_INFO,
    GUI_LABEL_DE_FW_VERSION,
    GUI_LABEL_DE_MANUFACTURE_YEAR,
    GUI_LABEL_DE_LANGUAGE,
    GUI_LABEL_DE_LANGUAGE_2,
    GUI_LABEL_DE_AMPLIFIER_IS_ACTIVE,
    GUI_LABEL_DE_OVERTEMPERATURE,
    GUI_LABEL_DE_TEMPERATURE_WARNING,
    GUI_LABEL_DE_DC_VOLTAGE_DETECTED,
    GUI_LABEL_DE_CHECK_FUSES,
    GUI_LABEL_DE_NO_SIGNAL,
    GUI_LABEL_DE_STARTING_AMPLIFIER,
    GUI_LABEL_DE_ENABLE,
    GUI_LABEL_DE_EEPROM_ERROR,
    GUI_LABEL_DE_INPUT_MONITOR
};

const uint8_t statusLabelsPositions[3][8] = {
    {
        GUI_STATUS_OK_POS_EN,
        GUI_STATUS_OVERHEATED_POS_EN,
        GUI_STATUS_HIGHTEMP_POS_EN,
        GUI_STATUS_DC_POS_EN,
        GUI_STATUS_FUSES_POS_EN,
        GUI_STATUS_NOSIGNAL_POS_EN,
        GUI_STATUS_STARTING_POS_EN,
        GUI_STATUS_EEPROM_POS_EN
    }, {
        GUI_STATUS_OK_POS_DE,
        GUI_STATUS_OVERHEATED_POS_DE,
        GUI_STATUS_HIGHTEMP_POS_DE,
        GUI_STATUS_DC_POS_DE,
        GUI_STATUS_FUSES_POS_DE,
        GUI_STATUS_NOSIGNAL_POS_DE,
        GUI_STATUS_STARTING_POS_DE,
        GUI_STATUS_EEPROM_POS_DE
    }, {
        GUI_STATUS_OK_POS_HU,
        GUI_STATUS_OVERHEATED_POS_HU,
        GUI_STATUS_HIGHTEMP_POS_HU,
        GUI_STATUS_DC_POS_HU,
        GUI_STATUS_FUSES_POS_HU,
        GUI_STATUS_NOSIGNAL_POS_HU,
        GUI_STATUS_STARTING_POS_HU,
        GUI_STATUS_EEPROM_POS_HU
    }
};

// FUNCTIONS

uint8_t GUI_deinit(void) {

    if (!menuActive) {
        // DO DEINIT JOB!
        return 1;
    }

    // We are in the menu yet
    return 0;
}

const char * getLabel(uint8_t id) {

    switch(settings.language) {
        case GUI_LANG_EN:
            return en_labels[id];
        case GUI_LANG_DE:
            return de_labels[id];
        case GUI_LANG_HU:
            return hu_labels[id];
        default:
            return en_labels[id];
    }
}

void drawOnOffParameter(uint8_t pos, uint8_t isOn, uint8_t editing) {

    uint16_t color = editing ? GREEN : MAGENTA;
    char label[5];

    sprintf(label, "%s", isOn ? getLabel(GUI_LABEL_ON) :
                                getLabel(GUI_LABEL_OFF));

    redrawBgArea(280, textPos[pos], 40, 20);
    draw_text(label, 280, textPos[pos], Tahoma12, 2, color,1);
}

void drawLanguageParameter(uint8_t editing) {

    uint16_t color = editing ? GREEN : MAGENTA;

    redrawBgArea(285, textPos[4], 35, 20);

    draw_text(getLabel(GUI_LABEL_LANGUAGE_2), 250,
              textPos[4], Tahoma12, 2, color,1);
}

void drawNumericParameter(uint8_t pos, uint8_t value,
                          char * unit, uint8_t editing) {

    uint16_t color = editing ? GREEN : MAGENTA;
    char label[5];
    uint16_t vPos;

    if (value < 10) vPos = 280;
    else if (value < 100) vPos = 270;
    else vPos = 265;

    redrawBgArea(260, textPos[pos], 60, 20);
    sprintf(label, "%d", value);
    draw_text(label, vPos, textPos[pos], Tahoma12, 2, color,1);
    sprintf(label, "%s", unit);
    draw_text(label, 295, textPos[pos], Tahoma12, 2, color,1);
}

uint8_t getStatusLabelPosition(uint8_t id) {

    switch(settings.language) {
        case GUI_LANG_EN:
            return statusLabelsPositions[GUI_LANG_EN][id];
        case GUI_LANG_DE:
            return statusLabelsPositions[GUI_LANG_DE][id];
        case GUI_LANG_HU:
            return statusLabelsPositions[GUI_LANG_HU][id];
        default:
            return 10;
    }
}


void drawLoadingScreen() {

    ILI9341_Fill_Screen(BLACK);
    ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);

    drawStartLogo();
    draw_text(getLabel(GUI_LABEL_STARTING_AMPLIFIER),
                getStatusLabelPosition(GUI_STATUS_STARTING_POS),
                200, Tahoma14, 2, DARKGREY, 0);
}

void drawTemperarture() {

    uint16_t leftColor = WHITE;
    uint16_t rightColor = WHITE;

    if (tempLeft >= settings.warningTemperature) leftColor = ORANGE;
    if (tempRight >= settings.warningTemperature) rightColor = ORANGE;
    if (tempLeft >= settings.switchOffTemperature) leftColor = RED;
    if (tempRight >= settings.switchOffTemperature) rightColor = RED;

    char val[10];

    // °C
    sprintf(val, "%d °C", tempLeft);
    uint8_t w = draw_text(val, 20, 4, Tahoma14, 2, leftColor,1);
    redrawBgArea(20 + w, 4, 50,25);

    sprintf(val, "%d °C", tempRight);

    if (tempRight > 99) {
        uint8_t w = draw_text(val, 247, 4, Tahoma14, 2, rightColor,1);
        redrawBgArea(247 + w, 8, 25,25);
    }

    else {
        uint8_t w = draw_text(val, 257, 4, Tahoma14, 2, rightColor,1);
        redrawBgArea(257 + w, 8, 25,25);
    }
}

void drawOKIcon(void) {

    ILI9341_Draw_Filled_Circle(160, 145, 30, GREEN);
    ILI9341_Draw_Filled_Circle(145, 150, 3, WHITE);
    ILI9341_Draw_Filled_Circle(150, 155, 3, WHITE);
    ILI9341_Draw_Filled_Circle(155, 160, 3, WHITE);
    ILI9341_Draw_Filled_Circle(160, 155, 3, WHITE);
    ILI9341_Draw_Filled_Circle(165, 150, 3, WHITE);
    ILI9341_Draw_Filled_Circle(170, 145, 3, WHITE);
    ILI9341_Draw_Filled_Circle(175, 140, 3, WHITE);
}

void drawWarningIcon(void) {

    ILI9341_Draw_Filled_Circle(160, 145, 30, YELLOW);
    ILI9341_Draw_Filled_Rectangle_Coord(157, 125, 165, 149, BLACK);

    ILI9341_Draw_Filled_Circle(160, 159, 4, BLACK);
}

void drawFaultIcon(void) {

    ILI9341_Draw_Filled_Circle(160, 145, 30, RED);
    ILI9341_Draw_Filled_Rectangle_Coord(157, 125, 165, 149, WHITE);

    ILI9341_Draw_Filled_Circle(160, 159, 4, WHITE);
}

void drawStatusOK(void) {

    draw_text(getLabel(GUI_LABEL_AMPLIFIER_IS_ACTIVE),
                getStatusLabelPosition(GUI_STATUS_OK_POS),
                200, Tahoma14, 2, WHITE,1);

    drawOKIcon();
}

void drawStatusOverTemperature(void) {

    draw_text(getLabel(GUI_LABEL_OVERTEMPERATURE),
              getStatusLabelPosition(GUI_STATUS_OVERHEATED_POS),
              200, Tahoma14, 2, WHITE,1);

    drawFaultIcon();
}

void drawStatusHighTemperature(void) {

    draw_text(getLabel(GUI_LABEL_TEMPERATURE_WARNING),
              getStatusLabelPosition(GUI_STATUS_HIGHTEMP_POS),
              200, Tahoma14, 2, WHITE,1);

    drawWarningIcon();
}

void drawStatusDCOnOutput(void) {

    draw_text(getLabel(GUI_LABEL_DC_VOLTAGE_DETECTED),
              getStatusLabelPosition(GUI_STATUS_DC_POS),
              200, Tahoma14, 2, WHITE,1);

    drawFaultIcon();
}

void drawStatusCheckFuses(void) {

    draw_text(getLabel(GUI_LABEL_CHECK_FUSES),
              getStatusLabelPosition(GUI_STATUS_FUSES_POS),
              200, Tahoma14, 2, WHITE,1);

    drawFaultIcon();
}

void drawStatusShutDownTimer(int secs) {

    if (secs > settings.shutdownTimeout * 60)
        return;

    char val[32];
    char minutes;
    char format[10];

    minutes = secs / 60;
    secs -= minutes * 60;

    memset(format, 0, 10);
    if (minutes > 9) strcpy(format, "%d:");
    else strcpy(format, "0%d:");
    if (secs > 9) strcat(format, "%d");
    else strcat(format, "0%d");

    sprintf(val, format, minutes, secs);
    draw_text(val, 110, 130, Tahoma32, 5, DARKGREY,1);

    draw_text(getLabel(GUI_LABEL_NO_SIGNAL),
              getStatusLabelPosition(GUI_STATUS_NOSIGNAL_POS),
              200, Tahoma14, 2, WHITE,1);
}

void drawStatusEEPROMError(void) {

    draw_text(getLabel(GUI_LABEL_EEPROM_ERROR),
              getStatusLabelPosition(GUI_STATUS_EEPROM_POS),
              200, Tahoma14, 2, WHITE,1);

    drawWarningIcon();
}


void GUI_drawMainMenu() {

    uint16_t color[] = {DARKGREY,DARKGREY,DARKGREY,DARKGREY,DARKGREY,DARKGREY};
    color[selected] = WHITE;
    for (uint8_t i = 0; i < 6; i++) {
        redrawBgArea(0, cursorPos[i], 320, 1);
    }
    redrawBgArea(0, cursorPos[5] + 30, 320, 1);

    ILI9341_Draw_Horizontal_Line(5,cursorPos[selected],310, MAGENTA);
    ILI9341_Draw_Horizontal_Line(5,cursorPos[selected] + 30,310, MAGENTA);

    draw_text(getLabel(GUI_LABEL_CLIP_PROTECTION),
              15, textPos[0], Tahoma12, 2, color[0],1);

    draw_text(getLabel(GUI_LABEL_SHUTDOWN_TIMER),
              15, textPos[1], Tahoma12, 2, color[1],1);

    draw_text(getLabel(GUI_LABEL_DC_PROTECTION),
              15, textPos[2], Tahoma12, 2, color[2],1);

    draw_text(getLabel(GUI_LABEL_OVERHEAT_PROTECTION),
              15, textPos[3], Tahoma12, 2, color[3],1);

    draw_text(getLabel(GUI_LABEL_LANGUAGE),
              15, textPos[4], Tahoma12, 2, color[4],1);

    draw_text(getLabel(GUI_LABEL_INFO),
              15, textPos[5], Tahoma12, 2, color[5],1);

    // PARAMETERS
    drawOnOffParameter(2, settings.dcProtectionEnabled, 0);
    drawLanguageParameter(0);
}

void GUI_drawShutdownTimerMenu(uint8_t sel) {

    uint16_t color[] = {DARKGREY,DARKGREY,DARKGREY};
    color[sel] = WHITE;
    for (uint8_t i = 0; i < 3; i++) {
        redrawBgArea(0, cursorPos[i], 320, 1);
    }
    redrawBgArea(0, cursorPos[2] + 30, 320, 1);

    ILI9341_Draw_Horizontal_Line(5,cursorPos[sel],310, MAGENTA);
    ILI9341_Draw_Horizontal_Line(5,cursorPos[sel] + 30,310, MAGENTA);

    draw_text(getLabel(GUI_LABEL_ENABLE),
              15, textPos[0], Tahoma12, 2, color[0],1);

    draw_text(getLabel(GUI_LABEL_IDLE_TIME),
              15, textPos[1], Tahoma12, 2, color[1],1);

    draw_text(getLabel(GUI_LABEL_RESET_ON_KEYPRESS),
              15, textPos[2], Tahoma12, 2, color[2],1);

    drawOnOffParameter(0, settings.shutdownTimerEnabled, 0);
    drawNumericParameter(1, settings.shutdownTimeout, GUI_UNIT_MINUTES, 0);
    drawOnOffParameter(2, settings.shutdownResetEnabled, 0);
}

void GUI_drawClipProtectionMenu(uint8_t sel) {

    uint16_t color[] = {DARKGREY,DARKGREY};
    color[sel] = WHITE;
    for (uint8_t i = 0; i < 2; i++) {
        redrawBgArea(0, cursorPos[i], 320, 1);
    }
    redrawBgArea(0, cursorPos[1] + 30, 320, 1);

    ILI9341_Draw_Horizontal_Line(5,cursorPos[sel],310, MAGENTA);
    ILI9341_Draw_Horizontal_Line(5,cursorPos[sel] + 30,310, MAGENTA);

    draw_text(getLabel(GUI_LABEL_ENABLE),
              15, textPos[0], Tahoma12, 2, color[0],1);

    draw_text(getLabel(GUI_LABEL_DELAY),
              15, textPos[1], Tahoma12, 2, color[1],1);

    drawOnOffParameter(0, settings.clipProtectionEnabled, 0);
    drawNumericParameter(1, settings.clipDelayAfterStart, GUI_UNIT_SECONDS, 0);
}

void GUI_drawThermalProtectionMenu(uint8_t sel) {

    uint16_t color[] = {DARKGREY,DARKGREY};
    color[sel] = WHITE;
    for (uint8_t i = 0; i < 2; i++) {
        redrawBgArea(0, cursorPos[i], 320, 1);
    }
    redrawBgArea(0, cursorPos[1] + 30, 320, 1);

    ILI9341_Draw_Horizontal_Line(5,cursorPos[sel],310, MAGENTA);
    ILI9341_Draw_Horizontal_Line(5,cursorPos[sel] + 30,310, MAGENTA);

    draw_text(getLabel(GUI_LABEL_CRITICAL_TEMPRATURE),
              15, textPos[0], Tahoma12, 2, color[0],1);

    draw_text(getLabel(GUI_LABEL_WARNING_TEMPRATURE),
              15, textPos[1], Tahoma12, 2, color[1],1);

    drawNumericParameter(0, settings.switchOffTemperature, GUI_UNIT_CELSIUS, 0);
    drawNumericParameter(1, settings.warningTemperature, GUI_UNIT_CELSIUS, 0);
}

void GUI_drawInputs() {

    if (drawInputText) {
        draw_text("Signal", 60, GUI_MENU_TEXT_POS_0, Tahoma12, 2, WHITE,1);
        draw_text("DC", 60, GUI_MENU_TEXT_POS_1, Tahoma12, 2, WHITE,1);
        draw_text("Fuse L", 60, GUI_MENU_TEXT_POS_2, Tahoma12, 2, WHITE,1);
        draw_text("Fuse R", 60, GUI_MENU_TEXT_POS_3, Tahoma12, 2, WHITE,1);
        drawInputText = 0;
    }

    if (HAL_GPIO_ReadPin(SIGNAL_IN_GPIO_Port, SIGNAL_IN_Pin))
        ILI9341_Draw_Filled_Circle(25, 62, 5, GREEN);
    else redrawBgArea(20, 57,15,20);

    if (HAL_GPIO_ReadPin(DC_IN_GPIO_Port, DC_IN_Pin))
        ILI9341_Draw_Filled_Circle(25, 92, 5, GREEN);
    else redrawBgArea(20, 87,15,20);

    if (HAL_GPIO_ReadPin(FUSE_L_GPIO_Port, FUSE_L_Pin))
        ILI9341_Draw_Filled_Circle(25, 122, 5, GREEN);
    else redrawBgArea(20, 117,15,20);

    if (HAL_GPIO_ReadPin(FUSE_R_GPIO_Port, FUSE_R_Pin))
        ILI9341_Draw_Filled_Circle(25, 152, 5, GREEN);
    else redrawBgArea(20, 147,15,20);

}


void GUI_drawInfo(AmpIO_Button b) {

    static uint8_t monitorActive = 0;

    if(b == AMPIO_ESC) {
            if (!monitorActive) {
            ILI9341_drawBackground();
            submenuActive = 0;
            monitorActive = 0;
            GUI_drawMainMenu();
            return;
        }
    }
    else if(b == AMPIO_ENTER) {
        monitorActive ^= 1;
        drawInputText = monitorActive;
        ILI9341_drawBackground();
    }

    if (monitorActive) {
        GUI_drawInputs();
        return;
    }

    draw_text(getLabel(GUI_LABEL_FW_VERSION),
              20, 90, Tahoma12, 2, WHITE,1);

    draw_text(getLabel(GUI_LABEL_MANUFACTURE_YEAR),
              20, 110, Tahoma12, 2, WHITE,1);

    draw_text("http://chaos-dev.ml", 20, 130, Tahoma12, 2, WHITE,1);
    draw_text("Made with <3  in Germany", 20, 170, Tahoma12, 2, WHITE,1);
    draw_text(getLabel(GUI_LABEL_INPUT_MONITOR),
              20, 210, Tahoma12, 2, WHITE, 1);
}

void GUI_ClipMenu(AmpIO_Button b) {

    static uint8_t sel = 0;
    static uint8_t edit = 0;

    if(b != AMPIO_NOPE) {

        switch (b) {
            case AMPIO_DOWN:

                if(edit) {
                    if (sel == 0) {
                        settings.clipProtectionEnabled ^= 1;
                        drawOnOffParameter(0, settings.clipProtectionEnabled, 1);
                    }
                    else if (sel == 1) {
                        if(settings.clipDelayAfterStart > 1)
                            settings.clipDelayAfterStart --;
                        drawNumericParameter(1, settings.clipDelayAfterStart,
                                              GUI_UNIT_SECONDS, 1);
                    }
                }
                else {
                    if (sel < 1) {
                        sel ++;
                        GUI_drawClipProtectionMenu(sel);
                    }
                }
                break;
            case AMPIO_UP:
                if(edit) {
                    if (sel == 0) {
                        settings.clipProtectionEnabled ^= 1;
                        drawOnOffParameter(0, settings.clipProtectionEnabled, 1);
                    }
                    else if (sel == 1) {
                        if(settings.clipDelayAfterStart < 10)
                            settings.clipDelayAfterStart ++;
                        drawNumericParameter(1, settings.clipDelayAfterStart,
                                              GUI_UNIT_SECONDS, 1);
                    }
                }
                else {
                    if (sel > 0) {
                        sel --;
                        GUI_drawClipProtectionMenu(sel);
                    }
                }
                break;
            case AMPIO_ESC:
                if (edit) break;
                ILI9341_drawBackground();
                sel = 0;
                submenuActive = 0;
                edit = 0;
                GUI_drawMainMenu();
                break;
            case AMPIO_ENTER:
                edit ^= 1;
                if (sel == 0) {
                    drawOnOffParameter(0, settings.clipProtectionEnabled, edit);
                    if (!edit)
                        AmpIO_writeParameter(AMPIO_MEM_ADDR_CLIP_EN,
                            settings.clipProtectionEnabled);
                }
                else if (sel == 1) {
                    drawNumericParameter(1, settings.clipDelayAfterStart,
                                          GUI_UNIT_SECONDS, edit);
                    if (!edit)
                        AmpIO_writeParameter(AMPIO_MEM_ADDR_CLIP_DELAY,
                            settings.clipDelayAfterStart);
                }
                break;
            default:
                break;
        }
    }

}

void GUI_ShutdownMenu(AmpIO_Button b) {

    static uint8_t sel = 0;
    static uint8_t edit = 0;

    if(b != AMPIO_NOPE) {

        switch (b) {
            case AMPIO_DOWN:
                if(edit) {
                    if(sel == 0) {
                        settings.shutdownTimerEnabled ^= 1;
                        drawOnOffParameter(0, settings.shutdownTimerEnabled, 1);
                    }

                    else if(sel == 1) {
                        if (settings.shutdownTimeout > 1) {
                            settings.shutdownTimeout --;
                        }
                        drawNumericParameter(1, settings.shutdownTimeout,
                                              GUI_UNIT_MINUTES, 1);
                    }

                    else if(sel == 2) {
                        settings.shutdownResetEnabled ^= 1;
                        drawOnOffParameter(2, settings.shutdownResetEnabled, 1);
                    }
                }
                else {
                    if (sel < 2) {
                        sel ++;
                        GUI_drawShutdownTimerMenu(sel);
                    }
                }
                break;
            case AMPIO_UP:
                if(edit) {
                    if(sel == 0) {
                        settings.shutdownTimerEnabled ^= 1;
                        drawOnOffParameter(0, settings.shutdownTimerEnabled, 1);
                    }

                    else if(sel == 1) {
                        if (settings.shutdownTimeout < 99) {
                            settings.shutdownTimeout ++;
                        }
                        drawNumericParameter(1, settings.shutdownTimeout,
                                              GUI_UNIT_MINUTES, 1);
                    }

                    else if(sel == 2) {
                        settings.shutdownResetEnabled ^= 1;
                        drawOnOffParameter(2, settings.shutdownResetEnabled, 1);
                    }
                }
                else {
                    if (sel > 0) {
                        sel --;
                        GUI_drawShutdownTimerMenu(sel);
                    }
                }
                break;
            case AMPIO_ESC:
                if (edit) break;
                ILI9341_drawBackground();
                sel = 0;
                submenuActive = 0;
                edit = 0;
                GUI_drawMainMenu();
                break;
            case AMPIO_ENTER:
                edit ^= 1;
                if (sel == 0) {
                    drawOnOffParameter(0, settings.shutdownTimerEnabled, edit);
                    if (!edit)
                        AmpIO_writeParameter(AMPIO_MEM_ADDR_TIMER_EN,
                            settings.shutdownTimerEnabled);
                }
                else if (sel == 1) {
                    drawNumericParameter(1, settings.shutdownTimeout,
                                          GUI_UNIT_MINUTES, edit);
                    if (!edit)
                        AmpIO_writeParameter(AMPIO_MEM_ADDR_TIMEOUT,
                            settings.shutdownTimeout);
                }
                else if(sel == 2) {
                    drawOnOffParameter(2, settings.shutdownResetEnabled, edit);
                    if (!edit)
                        AmpIO_writeParameter(AMPIO_MEM_ADDR_TIMER_RESET_EN,
                            settings.shutdownResetEnabled);
                }
                break;
            default:
                break;
        }
    }
}

void GUI_ThermalMenu(AmpIO_Button b) {

    static uint8_t sel = 0;
    static uint8_t edit = 0;

    if(b != AMPIO_NOPE) {

        switch (b) {
            case AMPIO_DOWN:
                if (edit) {
                    if (sel == 0) {
                        if (settings.switchOffTemperature >
                            settings.warningTemperature + 5)
                                settings.switchOffTemperature --;

                        drawNumericParameter(0, settings.switchOffTemperature,
                                             GUI_UNIT_CELSIUS, 1);
                    }
                    else if (sel == 1) {
                        if(settings.warningTemperature > 25)
                            settings.warningTemperature --;

                        drawNumericParameter(1, settings.warningTemperature,
                                             GUI_UNIT_CELSIUS, 1);
                    }
                }
                else {
                    if (sel < 1) {
                        sel ++;
                        GUI_drawThermalProtectionMenu(sel);
                    }
                }
                break;
            case AMPIO_UP:
                if (edit) {
                    if (sel == 0) {
                        if (settings.switchOffTemperature < 150)
                                settings.switchOffTemperature ++;

                        drawNumericParameter(0, settings.switchOffTemperature,
                                             GUI_UNIT_CELSIUS, 1);
                    }
                    else if (sel == 1) {
                        if(settings.warningTemperature <
                            settings.switchOffTemperature - 5)
                            settings.warningTemperature ++;

                        drawNumericParameter(1, settings.warningTemperature,
                                             GUI_UNIT_CELSIUS, 1);
                    }
                }
                else {
                    if (sel > 0) {
                        sel --;
                        GUI_drawThermalProtectionMenu(sel);
                    }
                }
                break;
            case AMPIO_ESC:
                if (edit) break;
                ILI9341_drawBackground();
                sel = 0;
                submenuActive = 0;
                edit = 0;
                GUI_drawMainMenu();
                break;
            case AMPIO_ENTER:
                edit ^= 1;
                if (sel == 0) {
                    drawNumericParameter(0, settings.switchOffTemperature,
                                         GUI_UNIT_CELSIUS, edit);
                    if (!edit)
                        AmpIO_writeParameter(AMPIO_MEM_ADDR_OFF_TEMP,
                            settings.switchOffTemperature);
                }
                else if (sel == 1) {
                    drawNumericParameter(1, settings.warningTemperature,
                                         GUI_UNIT_CELSIUS, edit);
                    if (!edit)
                        AmpIO_writeParameter(AMPIO_MEM_ADDR_WARNING_TEMP,
                            settings.warningTemperature);
                }
                break;
            default:
                break;
        }
    }
}

void GUI_DCProtectionMenu(AmpIO_Button b) {

    if(b != AMPIO_NOPE) {

        switch (b) {
            case AMPIO_DOWN:
                settings.dcProtectionEnabled ^= 1;
                drawOnOffParameter(2, settings.dcProtectionEnabled, 1);
                break;
            case AMPIO_UP:
                settings.dcProtectionEnabled ^= 1;
                drawOnOffParameter(2, settings.dcProtectionEnabled, 1);
                break;
            case AMPIO_ENTER:
                drawOnOffParameter(2, settings.dcProtectionEnabled, 0);
                AmpIO_writeParameter(AMPIO_MEM_ADDR_DC_EN,
                    settings.dcProtectionEnabled);
                submenuActive = 0;
            default:
                break;
        }
    }
}


void GUI_LanguageMenu(AmpIO_Button b) {

    if(b != AMPIO_NOPE) {

        switch (b) {
            case AMPIO_DOWN:
                settings.language ++;
                if (settings.language == 3)
                    settings.language = 0;
                drawLanguageParameter(1);
                break;
            case AMPIO_UP:
                if (settings.language == 0)
                    settings.language = 2;
                else settings.language --;
                drawLanguageParameter(1);
                break;
            case AMPIO_ENTER:
                AmpIO_writeParameter(AMPIO_MEM_ADDR_LANGUAGE,
                    settings.language);
                ILI9341_drawBackground();
                GUI_drawMainMenu();
                submenuActive = 0;
            default:
                break;
        }
    }
}

void GUI_ShowStatus(uint8_t forced) {

    static uint8_t showBit = AMPIO_STATUS_OK;
    static uint8_t prevBit = AMPIO_STATUS_UNDEFINED;

    if (forced || refreshUIStatus || status & (1 << AMPIO_STATUS_TIMER)) {

        if (showBit != prevBit || forced) {
            ILI9341_drawBackground();
            drawTemperarture();
        }

        if (showBit != prevBit || showBit == AMPIO_STATUS_TIMER || forced) {

            if (forced) {
                for (showBit = AMPIO_STATUS_OK;
                     showBit < AMPIO_STATUS_UNDEFINED &&
                     !(status & (1 << showBit));
                     showBit ++);
            }

            switch (showBit) {
                case AMPIO_STATUS_OK:
                    drawStatusOK();
                    break;
                case AMPIO_STATUS_TEMP_WARNING:
                    drawStatusHighTemperature();
                    break;
                case AMPIO_STATUS_OVERHEATED:
                    drawStatusOverTemperature();
                    break;
                case AMPIO_STATUS_DC:
                    drawStatusDCOnOutput();
                    break;
                case AMPIO_STATUS_FUSES:
                    drawStatusCheckFuses();
                    break;
                case AMPIO_STATUS_TIMER:
                    drawStatusShutDownTimer(shutdownTimer);
                    break;
                case AMPIO_STATUS_EEPROM:
                    drawStatusEEPROMError();
                default:
                    break;
            }

            prevBit = showBit;
        }

        if (refreshUIStatus) {

            do {

                showBit ++;
                if (showBit == AMPIO_STATUS_UNDEFINED)
                    showBit = AMPIO_STATUS_OK;
            } while (!(status & (1 << showBit)));

            refreshUIStatus = 0;
        }
    }
}

void GUI_MainMenu(AmpIO_Button b) {

    if(!submenuActive) {

        if(b != AMPIO_NOPE) {

            switch (b) {
                case AMPIO_DOWN:
                    if (selected < 5) {
                        selected ++;
                        GUI_drawMainMenu();
                    }
                    break;
                case AMPIO_UP:
                    if (selected > 0) {
                        selected --;
                        GUI_drawMainMenu();
                    }
                    break;
                case AMPIO_ENTER:

                    if (selected != 2 && selected != 4) {
                        ILI9341_drawBackground();
                        submenuActive = 1;
                    }

                    switch (selected) {
                        case 0:
                            GUI_drawClipProtectionMenu(0);
                            break;
                        case 1:
                            GUI_drawShutdownTimerMenu(0);
                            break;
                        case 2:
                            drawOnOffParameter(2, settings.dcProtectionEnabled, 1);
                            submenuActive = 1;
                            break;
                        case 3:
                            GUI_drawThermalProtectionMenu(0);
                            break;
                        case 4:
                            submenuActive = 1;
                            drawLanguageParameter(1);
                            break;
                        default:
                            break;
                    }

                    break;
                case AMPIO_ESC:
                    ILI9341_drawBackground();
                    GUI_ShowStatus(1);
                    selected = 0;
                    menuActive = 0;
                    break;
                default:
                    break;
            }
        }
    }

    // show submenu
    else {
        switch (selected) {
            case 0:
                GUI_ClipMenu(b);
                break;
            case 1:
                GUI_ShutdownMenu(b);
                break;
            case 2:
                GUI_DCProtectionMenu(b);
                break;
            case 3:
                GUI_ThermalMenu(b);
                break;
            case 4:
                GUI_LanguageMenu(b);
                break;
            case 5:
                GUI_drawInfo(b);
                break;
            default:
                break;
        }
    }
}

void GUI_loop(AmpIO_Button b) {

    // Show mainscrenn
    if (!menuActive) {

        GUI_ShowStatus(0);

        if(b == AMPIO_ENTER) {
            ILI9341_drawBackground();
            menuActive = 1;
            GUI_drawMainMenu();
        }
    }

    else {
        GUI_MainMenu(b);
    }

    if (refreshUITemperature) {

        refreshUITemperature = 0;
        drawTemperarture();
    }
}

void GUI_init(void) {
    ILI9341_Init();

    selected = 0;
    menuActive = 0;
    submenuActive = 0;
    refreshUIStatus = 1,
    refreshUITemperature = 1;
    drawLoadingScreen();
}
