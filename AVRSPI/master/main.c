////////////////////////////////////////////////////////////////////////////////
//
//	Author:		Chaos Developing
//	Date:		2014-12-30
//	Compiler:	avr-gcc
//	Info:		ChaosHome Alarm System
//
////////////////////////////////////////////////////////////////////////////////

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "spi.h"
#include "Extension.h"
#include "SMC.h"

extern uint8_t extensionSlots[SMC_NUM_OF_SLOTS];

int main() {

	lcd_init();
	lcd_clear();
	SPI_init(SPI_MODE_MASTER);

	lcd_string(" SMC Controller ");
	lcd_setcursor(0,2);
	lcd_string("----------------");

	while(1) {

		SMC_extScan();

		lcd_setcursor(0,3);
		lcd_string("Slot:  ");

		for (uint8_t i = 0; i < SMC_NUM_OF_SLOTS; i ++) {
			if (extensionSlots[i] == EXT_TYPE_NOT_INSTALLED)
				lcd_string("-");
			else lcd_decimal(extensionSlots[i]);
			lcd_string(" ");
		}

		lcd_setcursor(0,4);
		lcd_string("State: ");
		for (uint8_t i = 0; i < SMC_NUM_OF_SLOTS; i ++) {
			if (extensionSlots[i] == EXT_TYPE_NOT_INSTALLED)
				lcd_string("0");
			else {
				if (SMC_extQuery(i, EXT_QUERY_STATE) == EXT_STATE_ON)
					lcd_string("1");
				else lcd_string("0");
			}
			lcd_string(" ");
		}

		_delay_ms(10);
	}

	return 0;
}
