/******************************************************************************
 * File Name: main_project.c
 * Description: mini_project_4
 * Author: mustafa awad
 ******************************************************************************/



#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include "ultra_sensor.h"


int main(void){

	uint16 dis =0 ;

	SREG |= (1<<7);  /*enable interrupt*/
	LCD_init();
	Ultrasonic_init();
	LCD_displayString(" The Distance =         cm");
	while(1){


		dis = Ultrasonic_readDistance();
		LCD_moveCursor(0,20);
		if(dis >= 100)
		{
			LCD_intgerToString(dis);
		}
		else
		{
			LCD_intgerToString(dis);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');

		}
		_delay_ms(300);

	}
}
