#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "i2c_slave.h"
#include "lcd.h"

#define Slave_Address			0x20

int main() {

    char buffer[10];
	int8_t count = 0;

    lcd_init();
	lcd_clear();
    I2C_Slave_Init(Slave_Address);

	lcd_setcursor(0,1);
	lcd_string("Slave Device");

	while (1)
	{
		switch(I2C_Slave_Listen())				/* Check for any SLA+W or SLA+R */
		{
			case 0:
			{
				lcd_setcursor(0,2);
            	lcd_string("Receiving :       ");
				do
				{
					sprintf(buffer, "%d    ", count);
					lcd_setcursor(13,2);
                	lcd_string(buffer);
					count = I2C_Slave_Receive();/* Receive data byte*/
				} while (count != -1);			/* Receive until STOP/REPEATED START received */
				count = 0;
				break;
			}
			case 1:
			{
				int8_t Ack_status;
				lcd_setcursor(0,3);
            	lcd_string("Sending :       ");
				do
				{
					Ack_status = I2C_Slave_Transmit(count);	/* Send data byte */
					sprintf(buffer, "%d    ",count);
					lcd_setcursor(13,3);
                	lcd_string(buffer);
					count++;
				} while (Ack_status == 0);		/* Send until Acknowledgment is received */
				break;
			}
			default:
				break;
		}
	}

    return 0;
}
