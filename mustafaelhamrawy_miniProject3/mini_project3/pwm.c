/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: source file for PWM with timer0 for AVR
 *
 * Author: mustafa elhamrawy
 *
 ******************************************************************************/


#include <avr/io.h>
#include "pwm.h"

#include "common_macros.h"
#include "gpio.h"

/******************************************************************************
 *****************           function definition        **********************/

/* Description
 * this fn is used to trigger the Timer0 with the PWM mode
 * set PWM with Non-inverting
 * pre-scaler ---> F_CPU/8
 * * Generate a PWM signal with frequency 500Hz
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * the input is duty cycle  (( 0 to 100 ))
 * */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0; //Set Timer Initial value

	OCR0 = (uint8)(((uint16)duty_cycle*255)/100);


	GPIO_setupPinDirection(PORTB_ID, OC0_ID, PIN_OUTPUT);   /* Configure PB3/OC0 as output pin */

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
