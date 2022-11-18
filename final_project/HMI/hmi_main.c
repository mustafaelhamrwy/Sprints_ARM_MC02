/*
 * hmi_main.c

 *      Author: mustafa awad Elhamrawy
 */

#define F_CPU 8000000UL
#include "lcd.h"
#include "keypad.h"
#include "std_types.h"
#include "uart.h"
#include "common_macros.h"
#include "util/delay.h"

/*******************************************************************************
 *****************                Definitions             *********************/
#define PASSWORD_SIZE        6      /* message send by Control ECU to HMI ECU*/
#define MC2_READY            0x01   /* message send by Control ECU to HMI ECU*/
#define MAIN_PASSWORD        0x02   /* message send by Control ECU to HMI ECU*/
#define COMPARE_PASSWORD     0x03   /* message send by Control ECU to HMI ECU*/
#define IDEDENTICAL_PASSWORD 0x04   /* message send by Control ECU to HMI ECU*/
#define OPEN_DOOR            0x05   /* message send by Control ECU to HMI ECU*/
#define DOOR_OPENED          0x06   /* message send by Control ECU to HMI ECU*/
#define DOOR_CLOSED          0x07   /* message send by Control ECU to HMI ECU*/
#define ERROR_ALARM          0x08   /* message send by Control ECU to HMI ECU*/
#define SAFED                0x09   /* message send by Control ECU to HMI ECU*/

/*******************************************************************************
 *********************       Global variable        ***************************/
static uint8 counter_wrong_pass =0 ;   /*using for count the number of wrong password in opening part*/
static uint8 counter_change_pass =0 ;  /*using for count the number of wrong password in change password part*/

void get_password(uint8 *password);
void send_password(uint8 *password);
uint8 check_password (uint8 *password,uint8 *c_password);
void init_password();
void open_door(void);
void change_password(void);
void door_status(void);




int main(void){

	UART_ConfigFrame uart_config ={DATA_BITS_8,DISABLED,STOP_BIT_1,9600};  /*configuration of UART*/
	UART_init(&uart_config);
	LCD_init();
	init_password();
	while(1)
	{
		door_status();
	}
}

/*******************************************************************************
 *********************     Functions Definitions    ***************************/
/*
 * Description :
 * Function used to get password and save it in password array.
 */
void get_password(uint8 *password){

	uint8 i ;
	for(i=0 ;i<PASSWORD_SIZE;i++){
		password[i]= KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);
	}
}
/******************************************************************************/
/*
 * Description :
 * Function used to send password to second MCU.
 * send byte by byte
 */
void send_password(uint8 *password){

	uint8 i ;

	for(i=0;i<PASSWORD_SIZE;i++){
		if(UART_recieveByte()==MC2_READY){
			UART_sendByte(password[i]);

		}
	}
}
/******************************************************************************/
/*
 * Description :
 * Function used to check if the main password equal to confirmed password or not.
 * it return value may be 0 or 1 this returned value used in init_password function
 */

uint8 check_password (uint8 *password,uint8 *c_password){
	uint8 i ;
	for(i=0 ; i< PASSWORD_SIZE;i++)
	{
		if(password[i]!=c_password[i])
		{
			return FALSE;
		}
	}
	return TRUE ;
}
/******************************************************************************/
/*
 * Description :
 *                       PART1 IN THE PROJECT
 *it is the first fn that it used to take the main password
 */
void init_password(){
	uint8 password[PASSWORD_SIZE];
	uint8 c_password[PASSWORD_SIZE];        /*confirm password*/
	LCD_clearScreen();
	LCD_displayString("plz Enter 6 ");
	LCD_displayStringRowColumn(1,0,"digits password");
	_delay_ms(1500);
	LCD_clearScreen();
	LCD_displayString("Enter password");
	LCD_moveCursor(1,0);
	get_password(password);

	LCD_clearScreen();
	LCD_displayString("enter password");
	LCD_moveCursor(1,0);
	get_password(c_password);

	LCD_clearScreen();
	if(check_password(password, c_password)==FALSE){
		LCD_displayString("not matched");
		_delay_ms(300);
		LCD_clearScreen();
		LCD_displayString("please re_enter");
		LCD_displayStringRowColumn(1,5,"password");
		_delay_ms(1000);
		init_password();
	}
	else
	{
		LCD_displayString("confirmed");
		_delay_ms(1000);
		UART_sendByte(MAIN_PASSWORD);
		send_password(password);
	}

}
/******************************************************************************/
void open_door(void){
	uint8 entered_password[PASSWORD_SIZE];
	counter_wrong_pass++;
	/* check the password */
	if(counter_wrong_pass==4)
	{
		LCD_clearScreen();
		UART_sendByte(ERROR_ALARM);
		LCD_displayStringRowColumn(0,5,"ERROR");
		while(UART_recieveByte()!=SAFED)
		{
			/*waiting */
		}
		counter_wrong_pass=0;
		door_status();
	}

	LCD_clearScreen();
	LCD_displayString("Enter Password");
	LCD_moveCursor(1,0);
	get_password(entered_password);

	UART_sendByte(COMPARE_PASSWORD);
	send_password(entered_password);

	UART_sendByte(MC2_READY);
	if(UART_recieveByte()==IDEDENTICAL_PASSWORD)
	{
		UART_sendByte(OPEN_DOOR);
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,5,"Opening");
		while(UART_recieveByte()!=DOOR_OPENED)
		{
			/*waiting the door opening*/
		}
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,5,"Closing");
		while(UART_recieveByte()!=DOOR_CLOSED)
		{
			/*waiting the door closing*/
		}
		counter_wrong_pass=0;
		door_status();
	}
	else
	{
		LCD_clearScreen();
		LCD_displayString("Wrong Password!");
		_delay_ms(1000);
		open_door();
	}


}
/******************************************************************************/
void change_password(void){
	uint8 entered_password[PASSWORD_SIZE];

	counter_change_pass++;
	/*********** check the password ****************/
	if(counter_change_pass==4)
	{
		LCD_clearScreen();
		UART_sendByte(ERROR_ALARM);
		LCD_displayString("ERROR!");
		while(UART_recieveByte()!=SAFED)
		{
			/*waiting */
		}
		counter_wrong_pass=0;
		door_status();
	}

	LCD_clearScreen();
	LCD_displayString("Enter Password");
	LCD_moveCursor(1,0);
	get_password(entered_password);
	UART_sendByte(COMPARE_PASSWORD);
	send_password(entered_password);
	UART_sendByte(MC2_READY);


	if(UART_recieveByte()==IDEDENTICAL_PASSWORD)
	{
		init_password();
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,5, "done");
		counter_change_pass=0;
		door_status();
	}
	else
	{
		LCD_clearScreen();
		LCD_displayString("Wrong Password");
		_delay_ms(1000);
		change_password();
	}

}
/******************************************************************************/
/*
 * Description :
 *                       PART2 IN THE PROJECT
 * show 2 chooses
 * 					+ for open the door
 *                  - for change password
 */
void door_status(void){
	LCD_clearScreen();
	LCD_displayString("    Welcome");
	_delay_ms(2000);
	LCD_clearScreen();
	LCD_displayString("+ : Open door");
	LCD_displayStringRowColumn(1,0,"- : Change pass");
	while(KEYPAD_getPressedKey()!='+' && KEYPAD_getPressedKey()!='-'){
		/*don't do anything */
	}
	if(KEYPAD_getPressedKey() == '+'){
		_delay_ms(500);
		open_door();
	}
	else if (KEYPAD_getPressedKey() == '-') {
		_delay_ms(500);
		change_password();
	}
}

/*******************************************************************************
 *********************         main Function        ***************************/


