 /****************************************************************************** *
 * Module: ultra-sonic Sensor
 *
 * File Name: ultra_sensor.h
 *
 * Description: header file for the HCSR04 Ultra-sonic sensor driver
 *
 * Author: mustafa awad
 *
 *******************************************************************************/

#ifndef ULTRA_SENSOR_H_
#define ULTRA_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 ***********************          Definitions          ************************/

#define TRIGGERING_PORT     PORTB_ID
#define TRIGGERING_PIN      PIN5_ID


void Ultrasonic_init(void);

/* Description:
 * used to Send the Trigger pulse to the ultra-sonic
 * */
void Ultrasonic_Trigger(void);

/* Description:
 * Start the measurements by the ICU
 * return The measured distance in CM
 * */
uint16 Ultrasonic_readDistance(void);

/* Description:
 *  the call back function called by the ICU driver.
 *  used to calculate the pulse time generated by the ultra-sonic sensor
 * */
void Ultrasonic_edgeProcessing(void);




#endif /* ULTRA_SENSOR_H_ */
