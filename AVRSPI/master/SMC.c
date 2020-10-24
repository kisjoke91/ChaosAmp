#include "SMC.h"
#include "Extension.h"
#include "spi.h"
#include <util/delay.h>

volatile uint8_t extensionSlots[SMC_NUM_OF_SLOTS];
const uint8_t ssLines[SMC_NUM_OF_SLOTS] = {
	SPI_PIN_SS0,
	SPI_PIN_SS1,
	SPI_PIN_SS2,
	SPI_PIN_SS3,
	SPI_PIN_SS4
};


uint8_t SMC_querySlave(uint8_t slot, uint8_t data) {

	if (slot >= SMC_NUM_OF_SLOTS)
		return EXT_TYPE_NOT_INSTALLED;

	SPI_selectSlave(ssLines[slot]);
	_delay_us(10);
	SPI_TxRx(data);
	_delay_us(10);
	data = SPI_TxRx(EXT_CMD_NOPE);
	SPI_deselectSlave(ssLines[slot]);
	_delay_us(10);

	return data;
}


void SMC_extScan(void) {

	uint8_t read;

	for (uint8_t i = 0; i < SMC_NUM_OF_SLOTS; i ++) {

		read = SMC_querySlave(i, EXT_QUERY_TYPE);
		if (read > EXT_TYPE_NOT_INSTALLED &&
			read <= EXT_TYPE_WIFI) {
			extensionSlots[i] = read;
		}
		else extensionSlots[i] = EXT_TYPE_NOT_INSTALLED;
	}
}


uint8_t SMC_extSwitchOn(uint8_t slot) {

	uint8_t ret = EXT_TYPE_NOT_INSTALLED;

	if (slot >= SMC_NUM_OF_SLOTS ||
		extensionSlots[slot] == EXT_TYPE_NOT_INSTALLED)
		return ret;

    for (uint8_t i = 0; i < SMC_NUM_OF_SLOTS; i ++) {

        if (i == slot)
            ret = SMC_querySlave(slot, EXT_CMD_ON);
        else SMC_querySlave(i, EXT_CMD_OFF);
    }

	return ret;
}

uint8_t SMC_extQuery(uint8_t slot, uint8_t data) {

	uint8_t ret = EXT_TYPE_NOT_INSTALLED;

	if (slot >= SMC_NUM_OF_SLOTS ||
		extensionSlots[slot] == EXT_TYPE_NOT_INSTALLED)
		return ret;

    ret = SMC_querySlave(slot, data);
	return ret;
}
