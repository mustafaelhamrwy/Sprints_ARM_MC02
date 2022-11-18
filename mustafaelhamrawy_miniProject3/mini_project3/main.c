/*
 ================================================================================================
 Name        : temp_sensor_example.c
 Author      : mustafa elhamrawy
 Description : Test the ADC driver designed with polling technique using LM35 Temperature Sensor
 Date        : 5/9/2015
 ================================================================================================
 */

#include "adc.h"
#include "lm35_sensor.h"
#include "lcd.h"
#include "pwm.h"
#include "motor.h"

int main(void)
{
	uint8 temp;
	LCD_init(); /* initialize LCD driver*/

	ADC_ConfigType ADC_config_ptr ={INTERNAL_VREF_2_56 , ADC_F_CPU_8 };
	ADC_init(&ADC_config_ptr); /* initialize ADC driver */
	DcMotor_Init();
	LCD_displayString("FAN is ");


	LCD_moveCursor(1,0);
	LCD_displayString("Temp =     C");
    while(1)
    {

		temp = LM35_getTemperature();

		if(temp<30)
		{
			LCD_moveCursor(0,7);
			LCD_displayString("off");
			DcMotor_Rotate(STOP,0);
		}
		else if((temp>=30) && (temp<60))
		{
			LCD_moveCursor(0,7);
			LCD_displayString("on ");
			DcMotor_Rotate(CLOCKWISE,25);

		}
		else if((temp>=60) && (temp<90))
				{
			        LCD_moveCursor(0,7);
			        LCD_displayString("on ");
					DcMotor_Rotate(CLOCKWISE,50);

				}
		else if((temp>=90) && (temp<120))
				{
			        LCD_moveCursor(0,7);
			        LCD_displayString("on ");
					DcMotor_Rotate(CLOCKWISE,75);

				}
		else
				{
			        LCD_moveCursor(0,7);
			        LCD_displayString("on ");
					DcMotor_Rotate(CLOCKWISE,100);

				}


		LCD_moveCursor(1,8);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);

			LCD_displayCharacter(' ');
		}
    }
}
