#ifndef __GUI_H__
#define __GUI_H__

#include <inttypes.h>
#include "AmpIO.h"

#define GUI_LANG_EN    0
#define GUI_LANG_DE    1
#define GUI_LANG_HU    2

#define GUI_LABEL_ON                            0
#define GUI_LABEL_EN_ON                         "On"
#define GUI_LABEL_DE_ON                         "Ein"
#define GUI_LABEL_HU_ON                         "Be"

#define GUI_LABEL_OFF                           1
#define GUI_LABEL_EN_OFF                        "Off"
#define GUI_LABEL_DE_OFF                        "Aus"
#define GUI_LABEL_HU_OFF                        "Ki"

#define GUI_LABEL_CLIP_PROTECTION               2
#define GUI_LABEL_EN_CLIP_PROTECTION            "Clip protection"
#define GUI_LABEL_DE_CLIP_PROTECTION            "Einschaltverzögerung"
#define GUI_LABEL_HU_CLIP_PROTECTION            "Koppanás védelem"

#define GUI_LABEL_DELAY                         3
#define GUI_LABEL_EN_DELAY                      "Delay after start"
#define GUI_LABEL_DE_DELAY                      "Verzögerung"
#define GUI_LABEL_HU_DELAY                      "Késleltetés"

#define GUI_LABEL_SHUTDOWN_TIMER                4
#define GUI_LABEL_EN_SHUTDOWN_TIMER             "Shutdown timer"
#define GUI_LABEL_DE_SHUTDOWN_TIMER             "Ausschalt-Timer"
#define GUI_LABEL_HU_SHUTDOWN_TIMER             "Kikapcsolási időzítő"

#define GUI_LABEL_IDLE_TIME                     5
#define GUI_LABEL_EN_IDLE_TIME                  "Idle time"
#define GUI_LABEL_DE_IDLE_TIME                  "Wartezeit"
#define GUI_LABEL_HU_IDLE_TIME                  "Tétlenségi idő"

#define GUI_LABEL_RESET_ON_KEYPRESS             6
#define GUI_LABEL_EN_RESET_ON_KEYPRESS          "Reset on keypress"
#define GUI_LABEL_DE_RESET_ON_KEYPRESS          "Auf tastendruck zurücksetzen"
#define GUI_LABEL_HU_RESET_ON_KEYPRESS          "Visszaállítás gombnyomásra"

#define GUI_LABEL_DC_PROTECTION                 7
#define GUI_LABEL_EN_DC_PROTECTION              "DC protection"
#define GUI_LABEL_DE_DC_PROTECTION              "DC-Erkennung"
#define GUI_LABEL_HU_DC_PROTECTION              "Egyenfeszültség védelem"

#define GUI_LABEL_OVERHEAT_PROTECTION           8
#define GUI_LABEL_EN_OVERHEAT_PROTECTION        "Overtheat protection"
#define GUI_LABEL_DE_OVERHEAT_PROTECTION        "Übertemperaturschutz"
#define GUI_LABEL_HU_OVERHEAT_PROTECTION        "Túlmelegedés védelem"

#define GUI_LABEL_CRITICAL_TEMPRATURE           9
#define GUI_LABEL_EN_CRITICAL_TEMPRATURE        "Switch-off temperature"
#define GUI_LABEL_DE_CRITICAL_TEMPRATURE        "Ausschalttemperatur"
#define GUI_LABEL_HU_CRITICAL_TEMPRATURE        "Kikapcsolási hőmérséklet"

#define GUI_LABEL_WARNING_TEMPRATURE            10
#define GUI_LABEL_EN_WARNING_TEMPRATURE         "Warning temperature"
#define GUI_LABEL_DE_WARNING_TEMPRATURE         "Warntemperatur"
#define GUI_LABEL_HU_WARNING_TEMPRATURE         "Figyelmezetési hőmérséklet"

#define GUI_LABEL_INFO                          11
#define GUI_LABEL_EN_INFO                       "About"
#define GUI_LABEL_DE_INFO                       "Information"
#define GUI_LABEL_HU_INFO                       "Információ"

#define GUI_LABEL_FW_VERSION                    12
#define GUI_LABEL_EN_FW_VERSION                 "Firmware: build 050220 rc1"
#define GUI_LABEL_DE_FW_VERSION                 "Firmware: build 050220 rc1"
#define GUI_LABEL_HU_FW_VERSION                 "Firmware: build 050220 rc1"

#define GUI_LABEL_MANUFACTURE_YEAR              13
#define GUI_LABEL_EN_MANUFACTURE_YEAR           "Manufacture year: 2019"
#define GUI_LABEL_DE_MANUFACTURE_YEAR           "Baujahr: 2019"
#define GUI_LABEL_HU_MANUFACTURE_YEAR           "Gyártási év: 2019"

#define GUI_LABEL_LANGUAGE                      14
#define GUI_LABEL_EN_LANGUAGE                   "Language"
#define GUI_LABEL_DE_LANGUAGE                   "Sprache"
#define GUI_LABEL_HU_LANGUAGE                   "Nyelv"

#define GUI_LABEL_LANGUAGE_2                    15
#define GUI_LABEL_EN_LANGUAGE_2                 "English"
#define GUI_LABEL_DE_LANGUAGE_2                 "Deutsch"
#define GUI_LABEL_HU_LANGUAGE_2                 "Magyar"

#define GUI_LABEL_AMPLIFIER_IS_ACTIVE           16
#define GUI_LABEL_EN_AMPLIFIER_IS_ACTIVE        "Amplifier is active"
#define GUI_LABEL_DE_AMPLIFIER_IS_ACTIVE        "Verstärker ist an"
#define GUI_LABEL_HU_AMPLIFIER_IS_ACTIVE        "Bekapcsolva"

#define GUI_LABEL_OVERTEMPERATURE               17
#define GUI_LABEL_EN_OVERTEMPERATURE            "Overtemperature"
#define GUI_LABEL_DE_OVERTEMPERATURE            "Übertemperatur"
#define GUI_LABEL_HU_OVERTEMPERATURE            "Túlmelegedés"

#define GUI_LABEL_TEMPERATURE_WARNING           18
#define GUI_LABEL_EN_TEMPERATURE_WARNING        "High temperature"
#define GUI_LABEL_DE_TEMPERATURE_WARNING        "Hohe Tempratur"
#define GUI_LABEL_HU_TEMPERATURE_WARNING        "Magas hőmérséklet"

#define GUI_LABEL_DC_VOLTAGE_DETECTED           19
#define GUI_LABEL_EN_DC_VOLTAGE_DETECTED        "DC Voltage detected"
#define GUI_LABEL_DE_DC_VOLTAGE_DETECTED        "Am Ausgang wurde DC erkannt"
#define GUI_LABEL_HU_DC_VOLTAGE_DETECTED        "DC-feszültség érzékelve"

#define GUI_LABEL_CHECK_FUSES                   20
#define GUI_LABEL_EN_CHECK_FUSES                "Check fuses"
#define GUI_LABEL_DE_CHECK_FUSES                "Sicherungen kontrollieren"
#define GUI_LABEL_HU_CHECK_FUSES                "Ellenőrizd a biztosítékokat"

#define GUI_LABEL_NO_SIGNAL                     21
#define GUI_LABEL_EN_NO_SIGNAL                  "No signal"
#define GUI_LABEL_DE_NO_SIGNAL                  "Kein Signal"
#define GUI_LABEL_HU_NO_SIGNAL                  "Nincs bemenőjel"

#define GUI_LABEL_STARTING_AMPLIFIER            22
#define GUI_LABEL_EN_STARTING_AMPLIFIER         "Starting amplifier"
#define GUI_LABEL_DE_STARTING_AMPLIFIER         "Bitte warten"
#define GUI_LABEL_HU_STARTING_AMPLIFIER         "Bekapcsolás"

#define GUI_LABEL_ENABLE                        23
#define GUI_LABEL_EN_ENABLE                     "Enable"
#define GUI_LABEL_DE_ENABLE                     "Aktivieren"
#define GUI_LABEL_HU_ENABLE                     "Állapot"

#define GUI_LABEL_EEPROM_ERROR                  24
#define GUI_LABEL_EN_EEPROM_ERROR               "EEPROM error"
#define GUI_LABEL_DE_EEPROM_ERROR               "EEPROM-Fehler"
#define GUI_LABEL_HU_EEPROM_ERROR               "EEPROM hiba"

#define GUI_LABEL_INPUT_MONITOR                 25
#define GUI_LABEL_EN_INPUT_MONITOR              "Enter: Show input monitor"
#define GUI_LABEL_DE_INPUT_MONITOR              "Eingabe: Eingänge zeigen"
#define GUI_LABEL_HU_INPUT_MONITOR              "Enter: Bemenetek mutatása"


#define GUI_MENU_CURSOR_POS_0                   52
#define GUI_MENU_CURSOR_POS_1                   82
#define GUI_MENU_CURSOR_POS_2                   112
#define GUI_MENU_CURSOR_POS_3                   142
#define GUI_MENU_CURSOR_POS_4                   172
#define GUI_MENU_CURSOR_POS_5                   202

#define GUI_MENU_TEXT_POS_0                     57
#define GUI_MENU_TEXT_POS_1                     87
#define GUI_MENU_TEXT_POS_2                     117
#define GUI_MENU_TEXT_POS_3                     147
#define GUI_MENU_TEXT_POS_4                     177
#define GUI_MENU_TEXT_POS_5                     207

#define GUI_UNIT_SECONDS                        "s"
#define GUI_UNIT_MINUTES                        "m"
#define GUI_UNIT_CELSIUS                        "°C"

#define GUI_STATUS_OK_POS                       0
#define GUI_STATUS_OK_POS_EN                    80
#define GUI_STATUS_OK_POS_DE                    87
#define GUI_STATUS_OK_POS_HU                    107

#define GUI_STATUS_OVERHEATED_POS               1
#define GUI_STATUS_OVERHEATED_POS_EN            83
#define GUI_STATUS_OVERHEATED_POS_DE            89
#define GUI_STATUS_OVERHEATED_POS_HU            99

#define GUI_STATUS_HIGHTEMP_POS                 2
#define GUI_STATUS_HIGHTEMP_POS_EN              83
#define GUI_STATUS_HIGHTEMP_POS_DE              88
#define GUI_STATUS_HIGHTEMP_POS_HU              78

#define GUI_STATUS_DC_POS                       3
#define GUI_STATUS_DC_POS_EN                    72
#define GUI_STATUS_DC_POS_DE                    27
#define GUI_STATUS_DC_POS_HU                    56

#define GUI_STATUS_FUSES_POS                    4
#define GUI_STATUS_FUSES_POS_EN                 109
#define GUI_STATUS_FUSES_POS_DE                 50
#define GUI_STATUS_FUSES_POS_HU                 50

#define GUI_STATUS_NOSIGNAL_POS                 5
#define GUI_STATUS_NOSIGNAL_POS_EN              124
#define GUI_STATUS_NOSIGNAL_POS_DE              115
#define GUI_STATUS_NOSIGNAL_POS_HU              90

#define GUI_STATUS_STARTING_POS                 6
#define GUI_STATUS_STARTING_POS_EN              87
#define GUI_STATUS_STARTING_POS_DE              107
#define GUI_STATUS_STARTING_POS_HU              108

#define GUI_STATUS_EEPROM_POS                   7
#define GUI_STATUS_EEPROM_POS_EN                97
#define GUI_STATUS_EEPROM_POS_DE                93
#define GUI_STATUS_EEPROM_POS_HU                102


void GUI_init(void);
void GUI_loop(AmpIO_Button b);
void GUI_ShowStatus(uint8_t forced);
uint8_t GUI_deinit(void);

#endif /* __GUI_H__ */
