 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/


#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 ****************                Types Deceleration         *******************/
typedef enum
{
	DATA_BITS_5, DATA_BITS_6, DATA_BITS_7, DATA_BITS_8, DATA_BITS_9=7
}UART_DataBits;

typedef enum
{
    DISABLED, EVEN_PARITY=2, ODD_PARITY
}UART_Parity;

typedef enum
{
    STOP_BIT_1, STOP_BIT_2
}UART_StopBitSelect;

typedef struct
{
	UART_DataBits data_bits;
	UART_Parity parity ;
	UART_StopBitSelect stop_bit_select ;
	uint32 baud_rate;

}UART_ConfigFrame;

/*******************************************************************************
 ********************    Functions Prototypes        ***************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Set the Frame (data bits, parity and stop bits).
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigFrame * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #


#endif /* UART_H_ */
