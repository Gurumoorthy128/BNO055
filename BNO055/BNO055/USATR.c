/*
 * USATR.c
 *
 * Created: 9/30/2020 6:46:57 PM
 *  Author: Gurumoorthy S
 */ 

#include "USART.h"
#include <avr/io.h>
#include <stdlib.h>
#define F_CPU 16000000UL

void UART_init()
{
	UBRR0H=(BRC >> 8);
	UBRR0L=BRC;
	UCSR0B=(1<<TXEN0);
	UCSR0C=(1<<UCSZ00)|(1<<UCSZ01);
}

void UART_Tx_char(unsigned char data)
{
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0= data;
}

void UART_Tx_string(char* data)
{
	int next_char = 0;
	while(1)
	{
		if (*(data+next_char)!=0)
		{
			UART_Tx_char(*(data+next_char));
			++next_char;
			
		}
		else
		break;
	}
}