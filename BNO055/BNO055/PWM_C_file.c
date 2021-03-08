/*
 * PWM_C_file.c
 *
 * Created: 12/26/2020 11:04:42 PM
 *  Author: Gurumoorthy S
 */ 


#include "PWM_H_file.h"
void PWM_init()
{
	TCNT1 = 0;
	/*set fast PWM mode with non-inverted output*/
	TCCR1A |= (1<<WGM11) | (1<<COM1A1);
	TCCR1A &= ~(1<<COM1A0);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	ICR1 = 4999;
	port_out_com_1|=(1<<out_com_1_A);
	// port_out_com_0_A|=(1<out_com_0_A);  /*set OC0A pin as output*/
}

void start_timer(int pre_scaling)
{
	TCCR1B|= (pre_scaling & 0x07);
}

void duty_cycle(int duty)
{
	OCR1A = duty;
	while ( !( TIFR1 & (1<<OCF1A)) );
}