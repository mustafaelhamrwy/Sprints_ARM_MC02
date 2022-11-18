 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
}Adc_Channel;


typedef enum
{
    AREF,
    AVCC,
    INTERNAL_VREF_2_56=3
}Adc_ReferenceVolt;


typedef enum
{
    ADC_F_CPU_2,
	ADC_F_CPU_4=2,
	ADC_F_CPU_8,
	ADC_F_CPU_16,
	ADC_F_CPU_32,
	ADC_F_CPU_64,
	ADC_F_CPU_128
}ADC_Prescaler;

typedef struct
{
	Adc_ReferenceVolt     ref_volt;
	ADC_Prescaler         prescaler;
}ADC_ConfigType;



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(ADC_ConfigType *ADC_config_ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(Adc_Channel channel_num);

#endif /* ADC_H_ */
