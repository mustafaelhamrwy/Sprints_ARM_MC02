 /******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.h
 *
 * Description: Header file for the motor driver
 *
 * Author: mustafa elhamrawy
 *
 *******************************************************************************/

#include "gpio.h"


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 ****************                 Definitions                ******************/
#define DC_MOTOR_PORT_ID      PORTB_ID
#define DC_MOTOR_IN1_PIN_ID   PIN0_ID
#define DC_MOTOR_IN2_PIN_ID   PIN1_ID

/******************************************************************************
 *****************           types definition           **********************/
typedef enum{
	STOP , CLOCKWISE ,A_CLOCKWISE
}DcMotor_State;

/******************************************************************************
 *****************           function prototypes        **********************/

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);



#endif /* DC_MOTOR_H_ */

