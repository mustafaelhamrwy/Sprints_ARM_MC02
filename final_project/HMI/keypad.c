 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/
#include "common_macros.h"
#include "gpio.h"
#include "keypad.h"


/******************************************************************************
 *****************      static function prototypes      **********************/

#if(KEYPAD_COLUMNS_NUM==3)
static uint8 KEYPAD_4X3_adjustNumber(uint8 key_value);

#elif(KEYPAD_COLUMNS_NUM==4)
static uint8 KEYPAD_4X4_adjustNumber(uint8 key_value) ;
#endif

/******************************************************************************
 *****************           function definitions        **********************/


/* Description :
 * this function is configurable **size of keypad 4x4 or 4x3 , **Port_ID and pull up/pull down
 * return value of the pressed key
 */

uint8 KEYPAD_getPressedKey(void){
	uint8 column , row ;
	uint8 port_value =0 ;

	while(1)
	{
		for(column=0 ;column < KEYPAD_COLUMNS_NUM ;column++)
		{
			GPIO_setupPortDirection(KEYPAD_PORT_ID, PORT_INPUT);
			GPIO_setupPinDirection(KEYPAD_PORT_ID,KEYPAD_COLUMN_START_PIN+column,PIN_OUTPUT);
#if(KEYPAD_BUTTON_PRESSED== LOGIC_LOW)
			port_value = ~(1 << (KEYPAD_COLUMN_START_PIN + column));
#else
			//port_value = (1<<(KEYPAD_COLUMN_START_PIN + column));
#endif
			GPIO_writePort(KEYPAD_PORT_ID, port_value);
			for(row=0;row < KEYPAD_ROWS_NUM;row++)
			{
				if(GPIO_readPin(KEYPAD_PORT_ID,KEYPAD_ROW_START_PIN+row )==KEYPAD_BUTTON_PRESSED)
				{
					#if(KEYPAD_COLUMNS_NUM==3)
						return KEYPAD_4X3_adjustNumber(row*KEYPAD_COLUMNS_NUM + column +1) ;
					#elif(KEYPAD_COLUMNS_NUM==4)
						return KEYPAD_4X4_adjustNumber(row*KEYPAD_COLUMNS_NUM + column +1) ;
					#endif

				}
			}
		}
	}
}

#if(KEYPAD_COLUMNS_NUM==3)
/* Description :
 * this function used to correct the value of the pressed key for 4x3 keypad
 *
 */
static uint8 KEYPAD_4X3_adjustNumber(uint8 key_value){
	uint8 returned_value=0 ;
	switch(key_value)
	{
	case 10:
		returned_value = '*';
		break ;
	case 11 :
		returned_value = 0 ;
		break;
	case 12 :
		returned_value = '#' ;
		break;
	default :
		returned_value = key_value;
		break ;
	}

	return returned_value ;
}


#elif(KEYPAD_COLUMNS_NUM==4)
/* Description :
 * this function used to correct the value of the pressed key for 4x4 keypad
 *
 */
static uint8 KEYPAD_4X4_adjustNumber(uint8 key_value){
	uint8 returned_value=0 ;
	switch(key_value)
	{
	case 1:
		returned_value = 7;
		break ;
	case 2:
		returned_value = 8;
		break ;
	case 3:
		returned_value = 9;
		break ;
	case 4:
		returned_value = '/';
		break ;
	case 5:
		returned_value = 4;
		break ;
	case 6:
		returned_value = 5;
		break ;
	case 7:
		returned_value = 6;
		break ;
	case 8:
		returned_value = '*' ;
		break ;
	case 9:
		returned_value = 1;
		break ;
	case 10:
		returned_value = 2;
		break ;
	case 11:
		returned_value = 3;
		break ;
	case 12:
		returned_value = '-' ;
		break ;
	case 13:
		returned_value = 13 ;  /* ASCII OF ENTER*/
		break ;
	case 14:
		returned_value = 0;
		break ;
	case 15:
		returned_value = '=' ;
		break ;
	case 16:
		returned_value = '+' ;
		break ;
	default :
		returned_value = key_value;
		break ;
	}

	return returned_value ;
}
#endif



