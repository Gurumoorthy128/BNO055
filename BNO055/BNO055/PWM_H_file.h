/*
 * PWfileM_C_.h
 *
 * Created: 12/26/2020 11:03:55 PM
 *  Author: Gurumoorthy S
 */ 


#ifndef PWFILEM_C__H_
#define PWFILEM_C__H_



#define F_CPU 16000000UL					/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>

#define port_out_com_0_A DDRB  //output_compare_port for OC0A
#define port_out_com_0_B DDRG  //output_compare_port for OC0B
#define out_com_0_A PB7         //output_compare_pin for OC0A
#define out_com_0_B PG5         //output_compare_pin for OC0B


#define port_out_com_1 DDRB    //output_compare_port for OC1A & OC1B
#define out_com_1_A PB5         //output_compare_pin for OC1A
#define out_com_1_B PB6         //output_compare_pin for OC1B


#define port_out_com_2_A DDRB  //output_compare_port for OC2A
#define port_out_com_2_B DDRH  //output_compare_port for OC2B
#define out_com_2_A PB4         //output_compare_pin for OC2A
#define out_com_2_B PH6         //output_compare_pin for OC2B


#define port_out_com_3 DDRE    //output_compare_port for OC3A , OC3B , OC3C
#define out_com_3_A PE3         //output_compare_pin for OC3A
#define out_com_3_B PE4         //output_compare_pin for OC3B
#define out_com_3_C PE5         //output_compare_pin for OC3C


#define port_out_com_4 DDRH    //output_compare_port for OC4A , OC4B , OC4C
#define out_com_4_A PH3         //output_compare_pin for OC4A
#define out_com_4_B PH4         //output_compare_pin for OC4B
#define out_com_4_C PH5         //output_compare_pin for OC4C


#define port_out_com_5 DDRL    //output_compare_port for OC5A , OC5B , OC5C
#define out_com_5_A PL3         //output_compare_pin for OC5A
#define out_com_5_B PL4         //output_compare_pin for OC5B
#define out_com_5_C PL5         //output_compare_pin for OC5C

void PWM_init();
void start_timer(int pre_scaling);
void duty_cycle(int duty);


#endif /* PWFILEM_C__H_ */