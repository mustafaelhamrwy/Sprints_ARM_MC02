/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for PWM with timer0 for AVR
 *
 * Author: mustafa elhamrawy
 *
 **************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *****************                Definitions             *********************/
#define OC0_ID        PIN3_ID

/******************************************************************************
 *****************           function prototypes        **********************/

/* Description
 * this fn is used to trigger the Timer0 with the PWM mode
 * set PWM with Non-inverting
 * pre-scaler ---> F_CPU/8
 * * Generate a PWM signal with frequency 500Hz
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * the input is duty cycle  (( 0 to 100 ))
 * */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
