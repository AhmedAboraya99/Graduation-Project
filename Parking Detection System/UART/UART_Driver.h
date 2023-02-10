/*
 * UART_Driver.h
 *
 * Created: 12/27/2021 7:21:37 AM
 *  Author: Ahmed Aboraya
 */ 

#include "ATMEGA32.h"
#include "DIO_Driver.h"

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

void MCAL_USART_init();
void MCAL_USART_send_char(char Data);
char MCAL_USART_receive_char();
void MCAL_USART_send_string(char *p_Data);
char* MCAL_USART_receive_string();
void MCAL_USART_Clear();
//USART Macros
#define MYUBRR	51
/* UCSRA */

#define UDRE	5		//USART Data Register Empty
#define TXC		6		//USART Transmit Complete
#define RXC		7		//USART Receive Complete
#define U2X     1
#define MPCM    0
/* UCSRB */

#define RXEN	4		//USART Receive Enable
#define TXEN	3		//USART Transmit Enable
#define UCSZ2   2
#define RXB8    1
#define TXB8    0
/* UCSRC */
#define UCSZ0   0
#define UCSZ1   1
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6
#define URSEL   7

#endif /* UART_DRIVER_H_ */