/******************************************************************************
 * Model: main_project_control

 * Author: mustafa awad elhamrawy
 *****************************************************************************/

#define F_CPU 8000000UL

#include "std_types.h"
#include "common_macros.h"
#include "twi.h"
#include "external_eeprom.h"
#include "buzzer.h"
#include "motor.h"
#include "timer0.h"
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



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

#define EEPROM_ADDRESS       0X0311
#define THREE_SECONDS        94
#define FIFTEEN_SECONDS      469
#define ONE_MINUTE           1875

/*******************************************************************************
 *********************       Global variable        ***************************/
TIMER0_ConfigerType timer0_config={COMPARE_MODE,F_CPU_1024,0,250};  /*timer configuration*/

uint8 entered_password[PASSWORD_SIZE];
static uint32 g_tick=0;
/*******************************************************************************
 *********************     Functions Definitions    ***************************/
void save_new_password(void){
	uint8 i ;

	for(i=0;i<PASSWORD_SIZE;i++)
	{
		UART_sendByte(MC2_READY);
		EEPROM_writeByte(EEPROM_ADDRESS+i,UART_recieveByte());
		_delay_ms(10);
	}
}
/******************************************************************************/
void get_password(void){
	uint8 i ;

	for(i=0;i<PASSWORD_SIZE;i++)
	{
		UART_sendByte(MC2_READY);
		entered_password[i]=UART_recieveByte();
	}
}
/******************************************************************************/
uint8 check_password(void){
	uint8 password[PASSWORD_SIZE];
	for(uint8 i=0 ;i<PASSWORD_SIZE;i++)
	{
		EEPROM_readByte(EEPROM_ADDRESS+i,&password[i]);
		_delay_ms(10);
		if(password[i]!=entered_password[i]){
			return FALSE;
		}
	}
	return TRUE;
}
/******************************************************************************/
/*
 * Description :
 * used for open the door and close it again
 */
void open_stop_close(void){
	g_tick++ ;
	if(g_tick == FIFTEEN_SECONDS){
		DcMotor_Rotate(STOP);
		UART_sendByte(DOOR_OPENED);

	}
	if(g_tick ==(THREE_SECONDS+FIFTEEN_SECONDS)){
		DcMotor_Rotate(A_CLOCKWISE);
	}
	if(g_tick ==(THREE_SECONDS+FIFTEEN_SECONDS+FIFTEEN_SECONDS)){
		DcMotor_Rotate(STOP);
		UART_sendByte(DOOR_CLOSED);
		g_tick=0;
		TIMER0_deInit();
	}
}
/******************************************************************************/
/******************************************************************************/
/*
 * Description :
 * it is make buzzer on for 1 minute
 */
void alarm(void){
	g_tick++ ;
	if(g_tick == ONE_MINUTE){
		BUZZER_off();
		UART_sendByte(SAFED);
		g_tick=0;
		TIMER0_deInit();
	}
}
/*******************************************************************************
 *********************         main Function        ***************************/
int main(void){

	SREG |=(1<<7);  /*for interrupt */
	BUZZER_init();
	UART_ConfigFrame uart_config ={DATA_BITS_8,DISABLED,STOP_BIT_1,9600};  /*configuration of UART*/
	UART_init(&uart_config);
	TWI_init();


	while(1)
	{
		switch(UART_recieveByte())
		{
		case MAIN_PASSWORD:
			save_new_password();

			break ;
		case COMPARE_PASSWORD:
			get_password();
			if(check_password()==TRUE)
			{
				while(UART_recieveByte()!=MC2_READY)
				{
					/*****NOTHING******/
				}
				UART_sendByte(IDEDENTICAL_PASSWORD);
			}
			else
			{
				while(UART_recieveByte()!=MC2_READY)
				{
					/*****NOTHING******/
				}
				UART_sendByte(FALSE);
			}
			break;
		case OPEN_DOOR:
			g_tick=0;
			SREG |=(1<<7);
			TIMER0_setCallBack(open_stop_close);
			DcMotor_Init();
			DcMotor_Rotate(CLOCKWISE);
			TIMER0_init(&timer0_config);
			break;
		case ERROR_ALARM :
			g_tick=0;
			SREG |=(1<<7);
			TIMER0_setCallBack(alarm);
			TIMER0_init(&timer0_config);
			BUZZER_init();
			BUZZER_on();
		}
	}
}




