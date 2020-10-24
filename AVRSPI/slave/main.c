#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define SPI_PORT                        PORTB
#define SPI_DDR                         DDRB
#define SPI_PIN_MISO                    PB4

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
#define EXT_TYPE                        EXT_TYPE_BT

#define EXT_EN_PORT                     PORTD
#define EXT_EN_DDR                      DDRD
#define EXT_EN_PINX                     PIND
#define EXT_EN_PIN                      PD7


volatile uint8_t s = 0;
volatile uint8_t r = 0;
volatile uint8_t refresh = 0;
volatile uint8_t ie = 0;


void showReceived(uint8_t d) {

    lcd_clearrow(0,2);
    lcd_string("Recv: ");
    lcd_decimal(d);
}

void showSent(uint8_t d) {

    lcd_clearrow(0,3);
    lcd_string("Sent: ");
    lcd_decimal(d);
}

void EXT_off() {
    EXT_EN_PORT &= ~(1 << EXT_EN_PIN);
}

void EXT_on() {
    EXT_EN_PORT |= (1 << EXT_EN_PIN);
}

void init(void) {

    // Initialize interrupt for handle SS
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);    // Pull up for detecting node
    MCUCR |= (1 << ISC00);
    GICR |= (1 << INT0);

    // Initialize Enable pin
    EXT_EN_DDR |= (1 << EXT_EN_PIN);
    EXT_off();

    // Set up SPI
    SPI_DDR |= (1 << SPI_PIN_MISO);

    sei();
}

uint8_t SPI_TxRx(uint8_t data) {

    SPDR = data;
    while(!(SPSR & (1 << SPIF)));
    return SPDR;
}

int main() {

    lcd_init();
    lcd_clear();
    lcd_string("SPI Slave");
    init();

    while(1) {

        if (ie) {
            while(!(SPSR & (1 << SPIF)));
            r = SPDR;

            switch (r) {
                case EXT_CMD_ON:
                    EXT_on();
                    s = EXT_STATE_ON;
                    break;
                case EXT_CMD_OFF:
                    EXT_off();
                    s = EXT_STATE_OFF;
                    break;
                case EXT_QUERY_TYPE:
                    s = EXT_TYPE;
                    break;
                case EXT_QUERY_STATE:
                    s = (EXT_EN_PINX & (1 << EXT_EN_PIN)) ?
                        EXT_STATE_ON : EXT_STATE_OFF;
                    break;
                case EXT_CMD_NOPE:
                    break;
                default:
                    break;
            }

            SPDR = s;
        }
    }

    return 0;
}

ISR (INT0_vect) {

    // Falling edge
    if (!(PIND & (1 << PD2))) {
        SPCR |= (1 << SPE);
        ie = 1;
    }

    // Rising edge
    else {
        ie = 0;
        SPCR &= ~(1 << SPE);
        SPSR &= ~(1 << SPIF);
    }
}

/*switch (r) {
    case EXT_CMD_ON:
        EXT_on();
        s = EXT_STATE_ON;
        break;
    case EXT_CMD_OFF:
        EXT_off();
        s = EXT_STATE_OFF;
        break;
    case EXT_QUERY_TYPE:
        s = EXT_TYPE;
        break;
    case EXT_QUERY_STATE:
        s = (EXT_EN_PINX & (1 << EXT_EN_PIN)) ?
            EXT_STATE_ON : EXT_STATE_OFF;
        break;
    case EXT_CMD_NOPE:
        break;
    default:
        break;
}
refresh = 1;*/
