/*
 * timer.c
 *

 *      Author: mustafa awad
 */

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *****************          Global Variables      *****************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;



/*******************************************************************************
 ***********            Interrupt Service Routines        *********************/


ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after
		 the Timer0 overflow Interrupt occur */
		(*g_callBackPtr)();
	}
}


ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after
		 the Timer0 Compare Match Interrupt occur */
		(*g_callBackPtr)();
	}
}



/*******************************************************************************
 *****************     Functions Definitions           ************************/
/*
 * Description :
 * Function responsible for initialize for timer0
 * 			Setup Timer Mode
 * 			Setup Pre-scaler
 *          setup Compare value
 *          setup Timer initial value.
 */
void TIMER0_init(TIMER0_ConfigerType *config_ptr){

	TCCR0 |= (1<<FOC0);                                     /* It's activated in Non-PWM Mode */

	TCCR0 =  ((config_ptr->mode)<<WGM01) | (TCCR0 & 0xB7);  /* WGM00 bit is zero in Normal and Compare Modes*/
	                                                        /* WGM01 bit is zero in Normal Mode and 1 in Compare Mode */
	TCNT0 = (config_ptr->initial_value);                    /* initiate Timer0 value */
	OCR0 = (config_ptr->comper_value);                      /* Timer0 Compare Match Value */
	TCCR0 = (config_ptr->prescale) | (TCCR0 & 0xf8);       	/* insert timer clock */
	TIMSK |= (1<<OCIE0)|(1<<TOIE0);                         /* Enable overflow and Compare interrupts */
}



/* Description :
 * Function responsible for de-initialize for timer0
 */
void TIMER0_deInit(void){
	TCCR0 = 0;                          /* Reset Timer0 Mode and Clock(Stop Counting) */
	TCNT0 = 0;                          /* Reset Timer0 Register */
	OCR0  = 0;                          /* Reset Timer0  Compare Register */
	TIMSK &=~(1<<OCIE0);                /* Disabling Timer0 Overflow and Compare interrupts */
	TIMSK &=~(1<<TOIE0);
}



/* Description:
 	 Function to set the Call Back function address for timer0.
 */
void TIMER0_setCallBack(void(*a_ptr)(void)){

	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}



