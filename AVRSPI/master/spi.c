#include <util/delay.h>
#include <avr/interrupt.h>
#include "spi.h"

void SPI_init(uint8_t mode) {

    if (mode == SPI_MODE_MASTER) {

        SPI_DDR |= (1 << SPI_PIN_SCK) |
                   (1 << SPI_PIN_MOSI) |
    			   (1 << SPI_PIN_SS0) |
    			   (1 << SPI_PIN_SS1) |
    			   (1 << SPI_PIN_SS2) |
    			   (1 << SPI_PIN_SS3) |
    			   (1 << SPI_PIN_SS4);

        SPI_PORT |= (1 << SPI_PIN_SS0) |
                    (1 << SPI_PIN_SS1) |
                    (1 << SPI_PIN_SS2) |
                    (1 << SPI_PIN_SS3) |
                    (1 << SPI_PIN_SS4);

        SPCR |= (1 << MSTR);
        SPCR |= (1 << SPR0) | (0 << SPR1);
    }

    else {
        SPI_DDR |= (1 << SPI_PIN_MISO);
    }

    SPCR |= (1 << SPE);
    _delay_ms(1);
}

void SPI_disable(void) {

    SPCR &= ~(1 << SPE);
    SPSR &= ~(1 << SPIF);
}


void SPI_selectSlave(uint8_t  pin) {
    SPI_PORT &= ~(1 << pin);
}

void SPI_deselectSlave(uint8_t  pin) {
    SPI_PORT |= (1 << pin);
}

uint8_t SPI_TxRx(uint8_t data) {

    SPDR = data;
    while(!(SPSR & (1 << SPIF)));
    return SPDR;
}
