#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "i2c_master.h"
#include "lcd.h"

#define Slave_Write_Address		0x20
#define Slave_Read_Address		0x21
#define	count					10

int main() {

    lcd_init();
	lcd_clear();

    char buffer[10];
	I2C_Init();

	lcd_setcursor(0, 1);
    lcd_string("Master Device");

	while (1)
	{
		lcd_setcursor(0, 2);
        lcd_string("Sending :       ");
		I2C_Start_Wait(Slave_Write_Address);/* Start I2C communication with SLA+W */
		_delay_ms(5);
		for (uint8_t i = 0; i < count ; i++)
		{
			sprintf(buffer, "%d    ",i);
			lcd_setcursor(13,2);
            lcd_string(buffer);
			I2C_Write(i);					/* Send Incrementing count */
			_delay_ms(500);
		}
		lcd_setcursor(0, 3);
        lcd_string("Receiving :       ");
		I2C_Repeated_Start(Slave_Read_Address);	/* Repeated Start I2C communication with SLA+R */
		_delay_ms(5);
		for (uint8_t i = 0; i < count; i++)
		{
			if(i < count - 1)
				sprintf(buffer, "%d    ", I2C_Read_Ack());/* Read and send Acknowledge of data */
			else
				sprintf(buffer, "%d    ", I2C_Read_Nack());/* Read and Not Acknowledge to data */
			lcd_setcursor(13,3);
            lcd_string(buffer);
			_delay_ms(500);
		}
		I2C_Stop();							/* Stop I2C */
	}

    return 0;
}
