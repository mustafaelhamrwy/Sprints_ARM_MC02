 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *****************                Definitions             *********************/

#define KEYPAD_COLUMNS_NUM             4
#define KEYPAD_ROWS_NUM                4

#define KEYPAD_PORT_ID              PORTA_ID     /* configuration of keypad port*/

#define KEYPAD_ROW_START_PIN        PIN0_ID
#define KEYPAD_COLUMN_START_PIN     PIN4_ID

#define KEYPAD_BUTTON_PRESSED      LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED     LOGIC_HIGH


/******************************************************************************
 *****************           function prototypes        **********************/

/* Description :
 * this function is configurable **size of keypad 4x4 or 4x3 , **Port_ID and pull up/pull down
 * return value of the pressed key
 */


uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */

