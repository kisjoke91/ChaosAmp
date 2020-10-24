#ifndef __SPI_H__
#define __SPI_H__

#include <avr/io.h>


// ATMega 8
#define SPI_PORT                        PORTB
#define SPI_DDR                         DDRB
#define SPI_PINX                        PINB
#define SPI_PIN_SCK                     PB5
#define SPI_PIN_MISO                    PB4
#define SPI_PIN_MOSI                    PB3
#define SPI_PIN_SS0                     PB0
#define SPI_PIN_SS1                     PB1
#define SPI_PIN_SS2                     PB2
#define SPI_PIN_SS3                     PB6
#define SPI_PIN_SS4                     PB7

#define SPI_MODE_MASTER                 0
#define SPI_MODE_SLAVE                  1

void SPI_init(uint8_t mode);
void SPI_disable(void);
void SPI_selectSlave(uint8_t  pin);
void SPI_deselectSlave(uint8_t  pin);
uint8_t SPI_TxRx(uint8_t data);
uint8_t SPI_sTxRx(uint8_t data);
uint8_t SPI_masterQuery(uint8_t data);

#endif /* __SPI_H__ */
