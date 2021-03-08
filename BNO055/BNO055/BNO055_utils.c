/*
 * BNO055_utils.c
 *
 * Created: 12/22/2020 10:00:41 PM
 *  Author: Gurumoorthy S
 */ 

#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "I2C_Master_H_file.h"
#include "USART.h"
#include "BNO055_utils.h"

float TEMP()
{
	unsigned char temp;
	char String_Data[8];
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(TEMP_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	temp = I2C_Read_Nack();
	I2C_Stop();
	itoa(temp, String_Data, 10);
	UART_Tx_string("Temp: ");
	UART_Tx_string(String_Data);
	UART_Tx_string("\n");
	return temp;
}


/*****************************CALIBRATION STATUS DATA**********************************************/


int CALIB_STAT_ACC()
{
	int ACC_STAT;
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(CALIB_STAT_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	ACC_STAT = I2C_Read_Nack();
	I2C_Stop();
	_delay_ms(10);
 	if (((ACC_STAT>>3) & 1) & ((ACC_STAT>>2) & 1))
 		return 3;

	else if ((ACC_STAT>>2) & 1)
	{
		/*if ((ACC_STAT>>3) & 1)
		{
			return 3;
		}
		else*/
		return 1;
	}
	
	 else if((ACC_STAT>>3) & 1)
	{
		/*if((ACC_STAT>>2) & 1)
			return 3;
		else*/
			return 2;		
	}
	
	else
		return 0;
	//ACC_STAT = (ACC_STAT >> 2); //xxxx00xx
	/*if (ACC_STAT<<4)
	{
		
	}*/
	//ACC_STAT = (ACC_STAT<<4);
	//return (ACC_STAT>>6);
}

int CALIB_STAT_MAG()
{
	int ACC_STAT;
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(CALIB_STAT_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	ACC_STAT = I2C_Read_Nack();
	I2C_Stop();
	_delay_ms(10);
	if (((ACC_STAT>>1) & 1) & ((ACC_STAT>>0) & 1))
 		return 3;

	else if ((ACC_STAT>>0) & 1)
	{
		/*if ((ACC_STAT>>3) & 1)
		{
			return 3;
		}
		else*/
		return 1;
	}
	
	 else if((ACC_STAT>>1) & 1)
	{
		/*if((ACC_STAT>>2) & 1)
			return 3;
		else*/
			return 2;		
	}
	
	else
		return 0;
	/*if ( (ACC_STAT & (1<<1)) & (ACC_STAT & (1<<0)))
	return 3;
	else if ( (ACC_STAT & (1<<1)))
	return 2;
	else if ((ACC_STAT & (1<<0)))
	return 1;
	else
	return 0;*/
	//return ACC_STAT;
}

int CALIB_STAT_GYR()
{
	int ACC_STAT;
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(CALIB_STAT_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	ACC_STAT = I2C_Read_Nack();
	I2C_Stop();
	_delay_ms(10);
	if (((ACC_STAT>>5) & 1) & ((ACC_STAT>>4) & 1))
 		return 3;

	else if ((ACC_STAT>>4) & 1)
	{
		/*if ((ACC_STAT>>3) & 1)
		{
			return 3;
		}
		else*/
		return 1;
	}
	
	 else if((ACC_STAT>>5) & 1)
	{
		/*if((ACC_STAT>>2) & 1)
			return 3;
		else*/
			return 2;		
	}
	
	else
		return 0;
	/*if ( (ACC_STAT & (1<<5)) & (ACC_STAT & (1<<4)))//76543210
	return 3;
	else if ( (ACC_STAT & (1<<5)))
	return 2;
	else if ((ACC_STAT & (1<<4)))
	return 1;
	else
	return 0;*/
	//ACC_STAT = (ACC_STAT >> 4);
	//return ACC_STAT;
}

int CALIB_STAT_SYS()
{
	int ACC_STAT;
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(CALIB_STAT_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	ACC_STAT = I2C_Read_Nack();
	I2C_Stop();
	
	if (((ACC_STAT>>7) & 1) & ((ACC_STAT>>6) & 1))
 		return 3;

	else if ((ACC_STAT>>6) & 1)
	{
		/*if ((ACC_STAT>>3) & 1)
		{
			return 3;
		}
		else*/
		return 1;
	}
	
	 else if((ACC_STAT>>7) & 1)
	{
		/*if((ACC_STAT>>2) & 1)
			return 3;
		else*/
			return 2;		
	}
	
	else
		return 0;
		
	/*_delay_ms(10);
	if ( (ACC_STAT & (1<<7)) & (ACC_STAT & (1<<6)))
	return 3;
	else if ( (ACC_STAT & (1<<7)))
	return 2;
	else if ((ACC_STAT & (1<<6)))
	return 1;
	else
	return 0;*/
	//ACC_STAT = (ACC_STAT >> 6);
	//return ACC_STAT;
}


/*****************************EULAR DATA**********************************************/


float EULER_P()
{
	unsigned char Euler_Raw_LSB;
	unsigned char Euler_Raw_MSB;
	//char String_Data[16];
	float angle_vector_scale = 1.0f/16.0f;
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(EULER_P_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Euler_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(EULER_P_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Euler_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();	
	
	int16_t Euler_P_Raw = (Euler_Raw_MSB << 8) | (Euler_Raw_LSB);

	float Euler_P = ((float)(Euler_P_Raw)) * angle_vector_scale;
	return Euler_P;
}

float EULER_H()
{
	unsigned char Euler_Raw_LSB;
	unsigned char Euler_Raw_MSB;
	//char String_Data[16];
	float angle_vector_scale = 1.0f/16.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(EULER_H_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Euler_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(EULER_H_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Euler_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Euler_H_Raw = (Euler_Raw_MSB << 8) | (Euler_Raw_LSB);

	float Euler_H = ((float)(Euler_H_Raw)) * angle_vector_scale;
	return Euler_H;
	/*itoa(Euler_H, String_Data, 10);
	UART_Tx_string("Head: ");
	UART_Tx_string(String_Data);
	UART_Tx_string("\n");
	return Euler_H_Raw;*/
	//itoa(Euler_H, String_Data, 10);
	
}

float EULER_R()
{
	unsigned char Euler_Raw_LSB;
	unsigned char Euler_Raw_MSB;
	//char String_Data[16];
	float angle_vector_scale = 1.0f/16.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(EULER_R_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Euler_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(EULER_R_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Euler_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Euler_R_Raw = (Euler_Raw_MSB << 8) | (Euler_Raw_LSB);

	float Euler_R = ((float)(Euler_R_Raw)) * angle_vector_scale;
	return Euler_R;	
}


/*****************************GRAVITY DATA**********************************************/


float GRV_X()
{
	unsigned char Gravity_Raw_LSB;
	unsigned char Gravity_Raw_MSB;
	//char String_Data[16];
	float gravity_vector_scale = 1.0f/100.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GRAVITY_DATA_X_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gravity_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GRAVITY_DATA_X_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gravity_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Gravity_X_Raw = (Gravity_Raw_MSB << 8) | (Gravity_Raw_LSB);

	float Gravity_X = ((float)(Gravity_X_Raw)) * gravity_vector_scale;
	return Gravity_X;
}

float GRV_Y()
{
	unsigned char Gravity_Raw_LSB;
	unsigned char Gravity_Raw_MSB;
	//char String_Data[16];
	float gravity_vector_scale = 1.0f/100.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GRAVITY_DATA_Y_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gravity_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GRAVITY_DATA_Y_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gravity_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Gravity_Y_Raw = (Gravity_Raw_MSB << 8) | (Gravity_Raw_LSB);

	float Gravity_Y = ((float)(Gravity_Y_Raw)) * gravity_vector_scale;
	return Gravity_Y;
}

float GRV_Z()
{
	unsigned char Gravity_Raw_LSB;
	unsigned char Gravity_Raw_MSB;
	//char String_Data[16];
	float gravity_vector_scale = 1.0f/100.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GRAVITY_DATA_Z_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gravity_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GRAVITY_DATA_Z_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gravity_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Gravity_Z_Raw = (Gravity_Raw_MSB << 8) | (Gravity_Raw_LSB);

	float Gravity_Z = ((float)(Gravity_Z_Raw)) * gravity_vector_scale;
	return Gravity_Z;
}


/*****************************LINEAR ACCELERATION DATA**********************************************/


float LIA_X()
{
	unsigned char Linear_Accel_Raw_LSB;
	unsigned char Linear_Accel_Raw_MSB;
	//char String_Data[16];
	float Linear_Accel_scale = 1.0f/100.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(LINEAR_ACCEL_DATA_X_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Linear_Accel_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(LINEAR_ACCEL_DATA_X_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Linear_Accel_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Linear_Accel_X_Raw = (Linear_Accel_Raw_MSB << 8) | (Linear_Accel_Raw_LSB);

	float Linear_Accel_X = ((float)(Linear_Accel_X_Raw)) * Linear_Accel_scale;
	return Linear_Accel_X;
}


float LIA_Y()
{
	unsigned char Linear_Accel_Raw_LSB;
	unsigned char Linear_Accel_Raw_MSB;
	//char String_Data[16];
	float Linear_Accel_scale = 1.0f/100.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(LINEAR_ACCEL_DATA_Y_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Linear_Accel_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(LINEAR_ACCEL_DATA_Y_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Linear_Accel_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Linear_Accel_Y_Raw = (Linear_Accel_Raw_MSB << 8) | (Linear_Accel_Raw_LSB);

	float Linear_Accel_Y = ((float)(Linear_Accel_Y_Raw)) * Linear_Accel_scale;
	return Linear_Accel_Y;
}


float LIA_Z()
{
	unsigned char Linear_Accel_Raw_LSB;
	unsigned char Linear_Accel_Raw_MSB;
	//char String_Data[16];
	float Linear_Accel_scale = 1.0f/100.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(LINEAR_ACCEL_DATA_Z_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Linear_Accel_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(LINEAR_ACCEL_DATA_Z_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Linear_Accel_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Linear_Accel_Z_Raw = (Linear_Accel_Raw_MSB << 8) | (Linear_Accel_Raw_LSB);

	float Linear_Accel_Z= ((float)(Linear_Accel_Z_Raw)) * Linear_Accel_scale;
	return Linear_Accel_Z;
}

/*****************************ACCELERATION DATA**********************************************/


float ACC_X()
{
	unsigned char Accel_Raw_LSB;
	unsigned char Accel_Raw_MSB;
	//char String_Data[16];
	float Accel_scale = 1.0f/100.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(ACCEL_DATA_X_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Accel_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(ACCEL_DATA_X_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Accel_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Accel_X_Raw = (Accel_Raw_MSB << 8) | (Accel_Raw_LSB);

	float Accel_X= ((float)(Accel_X_Raw)) * Accel_scale;
	return Accel_X;
}


float ACC_Y()
{
	unsigned char Accel_Raw_LSB;
	unsigned char Accel_Raw_MSB;
	//char String_Data[16];
	float Accel_scale = 1.0f/100.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(ACCEL_DATA_Y_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Accel_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(ACCEL_DATA_Y_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Accel_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Accel_Y_Raw = (Accel_Raw_MSB << 8) | (Accel_Raw_LSB);

	float Accel_Y= ((float)(Accel_Y_Raw)) * Accel_scale;
	return Accel_Y;
}



float ACC_Z()
{
	unsigned char Accel_Raw_LSB;
	unsigned char Accel_Raw_MSB;
	//char String_Data[16];
	float Accel_scale = 1.0f/100.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(ACCEL_DATA_Z_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Accel_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(ACCEL_DATA_Z_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Accel_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Accel_Z_Raw = (Accel_Raw_MSB << 8) | (Accel_Raw_LSB);

	float Accel_Z= ((float)(Accel_Z_Raw)) * Accel_scale;
	return Accel_Z;
}



/*****************************GYROSCOPY DATA**********************************************/


float GYR_X()
{
	unsigned char Gyro_Raw_LSB;
	unsigned char Gyro_Raw_MSB;
	//char String_Data[16];
	float Angle_scale = 1.0f/16.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GYRO_DATA_X_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gyro_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GYRO_DATA_X_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gyro_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Gyro_X_Raw = (Gyro_Raw_MSB << 8) | (Gyro_Raw_LSB);

	float Gyro_X= ((float)(Gyro_X_Raw)) * Angle_scale;
	return Gyro_X;
}


float GYR_Y()
{
	unsigned char Gyro_Raw_LSB;
	unsigned char Gyro_Raw_MSB;
	//char String_Data[16];
	float Angle_scale = 1.0f/16.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GYRO_DATA_Y_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gyro_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GYRO_DATA_Y_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gyro_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Gyro_Y_Raw = (Gyro_Raw_MSB << 8) | (Gyro_Raw_LSB);

	float Gyro_Y= ((float)(Gyro_Y_Raw)) * Angle_scale;
	return Gyro_Y;
}



float GYR_Z()
{
	unsigned char Gyro_Raw_LSB;
	unsigned char Gyro_Raw_MSB;
	//char String_Data[16];
	float Angle_scale = 1.0f/16.0f;
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GYRO_DATA_Z_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gyro_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(GYRO_DATA_Z_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Gyro_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Gyro_Y_Raw = (Gyro_Raw_MSB << 8) | (Gyro_Raw_LSB);

	float Gyro_Y= ((float)(Gyro_Y_Raw)) * Angle_scale;
	return Gyro_Y;
}


/*****************************QUATRENION DATA**********************************************/


float QUAT_X()
{
	unsigned char Quat_Raw_LSB;
	unsigned char Quat_Raw_MSB;
	//char String_Data[16];
	float Quat_scale = 1.0f/pow(2.0f,14);
	
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(QUATERNION_DATA_X_LSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Quat_Raw_LSB = I2C_Read_Nack();
	I2C_Stop();

	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(QUATERNION_DATA_X_MSB_ADDR);		//Access LSB of Heading Euler angle
	I2C_Repeated_Start(BNO055_READ_ADDRESS);		//Set device address and read mode
	Quat_Raw_MSB = I2C_Read_Nack();
	I2C_Stop();

	int16_t Quat_X_Raw = (Quat_Raw_MSB << 8) | (Quat_Raw_LSB);

	float Quat_X= ((float)(Quat_X_Raw)) * Quat_scale;
	return Quat_X;
}



/*************************************Operation_Mode*********************************************/

void OPR_MODE_NDOF()
{
	I2C_Start_Wait(BNO055_WRITE_ADDRESS);	//Set device address and read mode
	I2C_Write(OPR_MODE_ADDR);
	I2C_Write(OPERATION_MODE_NDOF);		//Set operation mode to IMU
	I2C_Stop();
}


/*
float QUAT_Y();
float QUAT_Z();
float QUAT_W();*/