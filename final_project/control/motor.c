 /******************************************************************************
 *
 * Module: Motor
 *
 * File Name: motor.c
 *
 * Description: source file for the motor driver
 *
 * Author: mustafa elhamrawy
 *
 *******************************************************************************/

#include"motor.h"
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Functions Difenitions                                  *
 *******************************************************************************/

/*
 * Description :
 * 1.setup the direction for the Dc-Motor.
 * 2.Stop the DC-Motor at the beginning .
 */
void DcMotor_Init(void){
	/* configure motor pins as output pins */

	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, PIN_OUTPUT);

	/* Motor is stop at the beginning */
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);

}



void DcMotor_Rotate(DcMotor_State state){

	switch(state)
	{
	case STOP :
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	case CLOCKWISE :
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_HIGH);
		break;
	case A_CLOCKWISE :
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
		break;
	}
	//PWM_Timer0_Start(speed);
}
