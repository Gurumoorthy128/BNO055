/*
 * USART.h
 *
 * Created: 9/30/2020 6:47:21 PM
 *  Author: Gurumoorthy S
 */ 


#ifndef USART_H_
#define USART_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD)-1)
void UART_init();
void UART_Tx_char(unsigned char);
void UART_Tx_string(char*);


#endif /* USART_H_ */