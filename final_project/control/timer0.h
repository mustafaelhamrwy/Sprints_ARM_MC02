/*
 * timer0.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mustafa awad Elhamrawy
 */


#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_types.h"

/*******************************************************************************
 ****************                Types Deceleration         *******************/
typedef enum{
	OVERFLOW_MODE,COMPARE_MODE
}TIMER0_Mode;

typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}TIMER0_PreScale;

typedef struct{

	TIMER0_Mode        mode;
	TIMER0_PreScale    prescale;
	uint8              initial_value;
	uint8              comper_value;
}TIMER0_ConfigerType;

/*******************************************************************************
 ******************       Functions Prototypes      ***************************/

/*
 * Description :
 * Function responsible for initialize for timer0
 * 			Setup Timer Mode
 * 			Setup Pre-scaler
 *          setup Compare value
 *          setup Timer initial value.
 */
void TIMER0_init(TIMER0_ConfigerType *config_ptr);


/* Description:
 	 Function to set the Call Back function address for timer0.
 */

void TIMER0_setCallBack(void(*a_ptr)(void));

/* Description :
 * Function responsible for de-initialize for timer0
 */
void TIMER0_deInit(void);



#endif /* TIMER0_H_ */
