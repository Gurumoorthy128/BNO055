/*
 * BNO055.c
 *
 * Created: 12/15/2020 6:40:41 PM
 * Author : Gurumoorthy S
 */ 
#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "I2C_Master_H_file.h"
#include "USART.h"
#include "BNO055_utils.h"
#include "PWM_H_file.h"


void print(float);

/*
#define BNO055_Write 0x50 / *Write Address* /
#define BNO055_Read 0x51 / *Read Address* /
*/


/*
#define PCF8591_Write 0x90 / *0x90(PCF8591)* /
#define PCF8591_Read 0x91
*/


/*
uint8_t status_operator(uint8_t code)
{
	//UART_init();
	switch(code)
	{
		case 0x08:
		UART_Tx_char('s');  / *A START condition has not been transmitted* /
		//UART_Tx('\n');
		return 0;
		break;
		case 0x18:
		//UART_Tx(0x18);  / *SLA+W has been transmitted ACK has been received* /
		return 1;
		break;
		case 0x20:
		UART_Tx_char(0x20);  / *SLA+W has been transmitted NOT ACK has been received* /
		return 0;
		break;
		case 0x28:
		//UART_Tx(0x28);  / *Data byte has been transmitted ACK has been received* /
		return 1;
		break;
		case 0x30:
		UART_Tx_char(0x30);  / *Data byte has been transmitted NOT ACK has been received* /
		return 0;
		break;
		case 0x38:
		UART_Tx_char(0x38);  / *Arbitration lost in SLA+W or data bytes* /
		return 0;
		break;
		case 0x10:
		//UART_Tx(0x10);  / *A repeated START condition has not been transmitted* /
		return 0;
		break;
		case 0x40:
		//UART_Tx(0x40);  / *SLA+R has been transmitted ACK has been received* /
		return 1;
		break;
		case 0x48:
		//UART_Tx(0x48);  / *SLA+R has been transmitted NOT ACK has been received* /
		return 0;
		break;
		default:
		return 1;
		break;
	}
}*/
/*
void conf_Mode();
void Temp_conf();
void Temp_data();*/




int main(void)
{
	
	/********************************Variable_definition*****************************************/
	
	int status;
	float Eular_H_Raw , Eular_P_Raw , Eular_R_Raw;
	float GRV_X_Raw , GRV_Y_Raw , GRV_Z_Raw;
	float LIA_X_Raw , LIA_Z_Raw , LIA_Y_Raw;
	float strat_pos , x_dispalcement , y_displacement , z_displacement;
	float settime;
	char String_Data[16];
	int setpoint;
	
	/**********************************************************************************************/
	
	/****************************************Parameter_Initializatioin*****************************/
	
	I2C_Init();
	UART_init();
	//PWM_init();
	//start_timer(3);
	
	/***********************************************************************************************/
	/*conf_Mode();
	Temp_conf();*/
	
	UART_Tx_string("\t\t\t******************Hi*******************");
	
	
	
	
	
	
	
	
	
	//float Gravity_vector_scale = 1.0f/100.0f;
	//float Linear_vector_scale = 1.0f/100.0f;
	//float angle_vector_scale = 1.0f/16.0f;
	set_opr_as_NDOF;
	_delay_ms(10);
	
    while(1) 
    {
		
		UART_Tx_string("\nHello!");
		
		/***********************************displacement************************/
		
		
		
		/***********************************************************************/
		
		
		
		
		//TEMP();
			/******************servo control*****************************/	
		/*UART_Tx_string("Euler_Roll: ");
		print(EULER_R());
		UART_Tx_string("\t");
		
		setpoint = 90 - EULER_R();
		settime=((2.6 + (0.0522 * setpoint)) * 0.02) / 100;
		duty_cycle(settime/0.000004);
		//_delay_ms(10);
		
		UART_Tx_string("servo_angle: ");
		print(setpoint);
		UART_Tx_string("\n");*/
		/*********************************************************************/
		
		//GRV_X_Raw = GRV_X();
		
		UART_Tx_string("Gravity_X: ");
		print(GRV_X());
		UART_Tx_string("\t");
		
		//GRV_Y_Raw = GRV_Y();
		UART_Tx_string("Gravity_Y: ");
		print(GRV_Y());
		UART_Tx_string("\t");
		
		//GRV_Z_Raw = GRV_Z();
		UART_Tx_string("Gravity_Z: ");
		print(GRV_Z());
		UART_Tx_string("\n");
		
		/* //LIA_X_Raw = LIA_X();
		UART_Tx_string("LIA_X: ");
		print(LIA_X());
		UART_Tx_string("\t");
		
		//LIA_Y_Raw = LIA_Y();
		UART_Tx_string("LIA_Y: ");
		print(LIA_Y());
		UART_Tx_string("\t");
		
		//LIA_Z_Raw = LIA_Z();
		UART_Tx_string("LIA_Z: ");
		print(LIA_Z());
		UART_Tx_string("\n");
		
		UART_Tx_string("ACC_X: ");
		print(ACC_X());
		UART_Tx_string("\t");
		
		UART_Tx_string("ACC_Y: ");
		print(ACC_Y());
		UART_Tx_string("\t");
		
		UART_Tx_string("ACC_Z: ");
		print(ACC_Z());
		UART_Tx_string("\n");
		
		UART_Tx_string("GYR_X: ");
		print(GYR_X());
		UART_Tx_string("\t");
		
		UART_Tx_string("GYR_Y: ");
		print(GYR_Y());
		UART_Tx_string("\t");
		
		UART_Tx_string("GYR_Z: ");
		print(GYR_Z());
		UART_Tx_string("\n");
		
		
		UART_Tx_string("QUAT_X: ");
		print(QUAT_X());
		UART_Tx_string("\n");
		
		
		status = CALIB_STAT_SYS();
		itoa(status, String_Data, 10);			//Convert integer to string, radix=10
		UART_Tx_string("calib_sys: ");
		UART_Tx_string(String_Data);
		UART_Tx_string("\t");
		
		status = CALIB_STAT_GYR();
		itoa(status, String_Data, 10);			//Convert integer to string, radix=10
		UART_Tx_string("calib_gyr: ");
		UART_Tx_string(String_Data);
		UART_Tx_string("\t");
		
		status = CALIB_STAT_ACC();
		itoa(status, String_Data, 10);			//Convert integer to string, radix=10
		UART_Tx_string("calib_acc: ");
		UART_Tx_string(String_Data);
		UART_Tx_string("\t");
		
		status = CALIB_STAT_MAG();
		itoa(status, String_Data, 10);			//Convert integer to string, radix=10
		UART_Tx_string("calib_mag: ");
		UART_Tx_string(String_Data);
		UART_Tx_string("\t");
		
		Eular_P_Raw = EULER_P();
		//float Eular_P = (float)Eular_P_Raw * angle_vector_scale;
		itoa(Eular_P_Raw, String_Data, 10);			//Convert integer to string, radix=10
		UART_Tx_string("Pitch: ");
		UART_Tx_string(String_Data);
		UART_Tx_string("\t");
		
		Eular_H_Raw = EULER_H();
		//float Eular_H = (float)Eular_H_Raw * angle_vector_scale;
		itoa(Eular_H_Raw, String_Data, 10);			//Convert integer to string, radix=10
		UART_Tx_string("Head: ");
		UART_Tx_string(String_Data);
		UART_Tx_string("\t");
		
		Eular_R_Raw = EULER_R();
		//float Eular_H = (float)Eular_H_Raw * angle_vector_scale;
		itoa(Eular_R_Raw, String_Data, 10);			//Convert integer to string, radix=10
		UART_Tx_string("Roll: ");
		UART_Tx_string(String_Data);
		UART_Tx_string("\n");*/		
		
	}
}

void print(float Print_data)
{
	char String_Data[16];
	itoa(Print_data, String_Data, 10);        //Convert integer to string, radix=10
	//ftoa(Print_data, String_Data, 3);
	UART_Tx_string(String_Data);
	
}

