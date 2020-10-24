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
#include <avr/interrupt.h>
#include "lcd.h"
#include "spi.h"

#define SMC_NUM_OF_SLOTS				5

#define EXT_TYPE_NOT_INSTALLED			0
#define EXT_TYPE_RCA                    1
#define EXT_TYPE_BLANCED                2
#define EXT_TYPE_SPIDF                  3
#define EXT_TYPE_BT                     4
#define EXT_TYPE_WIFI                   5

#define EXT_CMD_ON                      6
#define EXT_CMD_OFF                     7
#define EXT_QUERY_TYPE                  8
#define EXT_QUERY_STATE                 9
#define EXT_CMD_NOPE                    255

#define EXT_STATE_ON                    10
#define EXT_STATE_OFF                   11



volatile uint8_t extensionSlots[SMC_NUM_OF_SLOTS];
const uint8_t ssLines[SMC_NUM_OF_SLOTS] = {
	SPI_PIN_SS0,
	SPI_PIN_SS1,
	SPI_PIN_SS2,
	SPI_PIN_SS3,
	SPI_PIN_SS4
};


void showReceived(uint8_t d) {
	lcd_clearrow(0,3);
	lcd_string("Recv: ");
	lcd_decimal(d);
}

void showSent(uint8_t d) {
	lcd_clearrow(0,2);
	lcd_string("Sent: ");
	lcd_decimal(d);
}

uint8_t SMC_querySlave(uint8_t slot, uint8_t data) {

	if (slot >= SMC_NUM_OF_SLOTS)
		return EXT_TYPE_NOT_INSTALLED;

	SPI_selectSlave(ssLines[slot]);
	_delay_us(10);
	SPI_TxRx(data);
	_delay_us(10);
	data = SPI_TxRx(EXT_CMD_NOPE);
	SPI_deselectSlave(ssLines[slot]);
	_delay_us(100);

	return data;
}


void SMC_scanExtensions(void) {

	uint8_t read;

	for (uint8_t i = 0; i < SMC_NUM_OF_SLOTS; i ++) {

		read = SMC_querySlave(i, EXT_QUERY_TYPE);
		if (read > EXT_TYPE_NOT_INSTALLED) {
			extensionSlots[i] = read;
		}
	}
}


int main() {

	lcd_init();
	lcd_clear();
	SPI_init(SPI_MODE_MASTER);

	SMC_scanExtensions();

	while(1) {

		static uint8_t i = 0;

		lcd_clearrow(0,1);
		lcd_string("Slot: ");

		for (uint8_t i = 0; i < SMC_NUM_OF_SLOTS; i ++) {
			lcd_decimal(extensionSlots[i]);
		}

		lcd_string(" (");
		lcd_decimal(i);
		lcd_string(")");

		lcd_clearrow(0,2);
		lcd_string("Slave type: ");
		lcd_decimal(SMC_querySlave(i, EXT_QUERY_TYPE));

		lcd_clearrow(0,3);
		lcd_string("On command: ");
		lcd_decimal(SMC_querySlave(i, EXT_CMD_ON));

		lcd_clearrow(0,4);
		lcd_string("Status: ");
		lcd_decimal(SMC_querySlave(i, EXT_QUERY_STATE));
		_delay_ms(1000);

		i ++;

		if (i > 4) {
			i = 0;
		}
	}

	return 0;
}
