/*
 * I2C_Master_C_file.c
 * Created: 12/9/2020 7:15:41 PM
 * Author : Gurumoorthy S
 */ 

/*

//#include "I2C_Master_H_file.h"								/ * Include I2C header file * /
#include "USART.h"
#include <compat/twi.h>



void I2C_Init()												/ * I2C initialize function * /
{
	TWBR = 0x48;							/ * Get bit rate register value by formula * /
}	


uint8_t I2C_Start(char write_address)						/ * I2C start function * /
{
	uint8_t status;											/ * Declare variable * /
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/ * Enable TWI, generate start condition and clear interrupt flag * /
	while (!(TWCR & (1<<TWINT)));							/ * Wait until TWI finish its current job (start condition) * /
	status = TWSR & 0xF8;									/ * Read TWI status register with masking lower three bits * /
	if (status != 0x08)										/ * Check weather start condition transmitted successfully or not? * /
	{
		//status = status_operator(0x08);
		return 0X08;										/ * If not then return status to indicate start condition fail * /
	}
	
	TWDR = write_address;									/ * If yes then write SLA+W in TWI data register * /
	TWCR = (1<<TWEN)|(1<<TWINT);							/ * Enable TWI and clear interrupt flag * /
	while (!(TWCR & (1<<TWINT)));							/ * Wait until TWI finish its current job (Write operation) * /
	status = TWSR & 0xF8;									/ * Read TWI status register with masking lower three bits * /	
	if (status == 0x18)										/ * Check weather SLA+W transmitted & ack received or not? * /
	{
		//status = status_operator(0x18);
		return 0X18;												/ * If yes then return status to indicate ack received i.e. ready to accept data byte * /
	}
	
	else if (status == 0x20)										/ * Check weather SLA+W transmitted & nack received or not? * /
	{
		//status = status_operator(0x20);
		return 0X20;												/ * If yes then return status to indicate nack received i.e. device is busy * /
	}
	else if (status == 0x38)
	{
		//status = status_operator(0x38);
		return 0X38;												/ * Else return status to indicate SLA+W failed * /
	}
	else 
	return 1;
}

uint8_t I2C_Repeated_Start(char read_address)				/ * I2C repeated start function * /
{
	uint8_t status;											/ * Declare variable * /
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/ * Enable TWI, generate start condition and clear interrupt flag * /
	while (!(TWCR & (1<<TWINT)));							/ * Wait until TWI finish its current job (start condition) * /
	status = TWSR & 0xF8;									/ * Read TWI status register with masking lower three bits * /
	if (status != 0x10)										/ * Check weather repeated start condition transmitted successfully or not? * /
	return 0x10;												/ * If no then return 0 to indicate repeated start condition fail * /
	TWDR = read_address;									/ * If yes then write SLA+R in TWI data register * /
	TWCR = (1<<TWEN)|(1<<TWINT);							/ * Enable TWI and clear interrupt flag * /
	while (!(TWCR & (1<<TWINT)));							/ * Wait until TWI finish its current job (Write operation) * /
	status = TWSR & 0xF8;									/ * Read TWI status register with masking lower three bits * /
	if (status == 0x40)										/ * Check weather SLA+R transmitted & ack received or not? * /
	return 0x40;												/ * If yes then return 1 to indicate ack received * / 
	if (status == 0x48)										/ * Check weather SLA+R transmitted & nack received or not? * /
	return 0x48;												/ * If yes then return 2 to indicate nack received i.e. device is busy * /
	else
	return 0x38;												/ * Else return 3 to indicate SLA+W failed * /
}

void I2C_Stop()												/ * I2C stop function * /
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					/ * Enable TWI, generate stop condition and clear interrupt flag * /
	while(TWCR & (1<<TWSTO));								/ * Wait until stop condition execution * / 
}

void I2C_Start_Wait(char write_address)
{
	uint8_t   twst;


	while ( 1 )
	{
		// send START condition
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		
		// wait until transmission completed
		while(!(TWCR & (1<<TWINT)));
		
		// check value of TWI Status Register. Mask prescaler bits.
		twst = TW_STATUS & 0xF8;
		if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
		
		// send device address
		TWDR = write_address;
		TWCR = (1<<TWINT) | (1<<TWEN);
		
		// wail until transmission completed
		while(!(TWCR & (1<<TWINT)));
		
		// check value of TWI Status Register. Mask prescaler bits.
		twst = TW_STATUS & 0xF8;
		if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) )
		{
			/ * device busy, send stop condition to terminate write operation * /
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
			
			// wait until stop condition is executed and bus released
			while(TWCR & (1<<TWSTO));
			
			continue;
		}
		//if( twst != TW_MT_SLA_ACK) return 1;
		break;
	}

	}/ * I2C_Start_Wait * /

uint8_t I2C_Write(unsigned char data)								/ * I2C write function * /
{
	uint8_t status;											/ * Declare variable * /
	TWDR = data;											/ * Copy data in TWI data register * /
	TWCR = (1<<TWEN)|(1<<TWINT);							/ * Enable TWI and clear interrupt flag * /
	while (!(TWCR & (1<<TWINT)));							/ * Wait until TWI finish its current job (Write operation) * /
	status = TWSR & 0xF8;									/ * Read TWI status register with masking lower three bits * /
	if (status == 0x28)										/ * Check weather data transmitted & ack received or not? * /
	{
		//status = status_operator(0x28);
		return 0X28;											/ * If yes then return status to indicate ack received * /
	}
	if (status == 0x30)										/ * Check weather data transmitted & nack received or not? * /
	{
		//status = status_operator(0x30);
		return 0X30;												/ * If yes then return status to indicate nack received * /
	}
	
	else if (status == 0x38)
	{
		//status_operator(0x38);
		return 0X38;												/ * Else return status to indicate data transmission failed * /
	}
	else 
	return 1;
	
}

char I2C_Read_Ack()											/ * I2C read ack function * /
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					/ * Enable TWI, generation of ack and clear interrupt flag * /
	while (!(TWCR & (1<<TWINT)));							/ * Wait until TWI finish its current job (read operation) * /
	return TWDR;											/ * Return received data * /
}	

unsigned char I2C_Read_Nack()										/ * I2C read nack function * /
{
	TWCR=(1<<TWEN)|(1<<TWINT);								/ * Enable TWI and clear interrupt flag * /
	while (!(TWCR & (1<<TWINT)));							/ * Wait until TWI finish its current job (read operation) * /
	return TWDR;											/ * Return received data * /
}	
*/


#include <inttypes.h>
#include <compat/twi.h>

#include "I2C_Master_H_file.h"


/* define CPU frequency in Hz here if not defined in Makefile */
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

/* I2C clock in Hz */
#define SCL_CLOCK  400000L


/*************************************************************************
 Initialization of the I2C bus interface. Need to be called only once
*************************************************************************/
void I2C_Init(void)
{
  /* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
  
  TWSR = 0;                         /* no prescaler */
  TWBR = ((F_CPU/SCL_CLOCK)-16)/2;  /* must be > 10 for stable operation */

}/* I2C_Init */


/*************************************************************************	
  Issues a start condition and sends address and transfer direction.
  return 0 = device accessible, 1= failed to access device
*************************************************************************/
unsigned char i2c_start(unsigned char address)
{
    uint8_t   twst;

	// send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;

	// send device address
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wail until transmission completed and ACK/NACK has been received
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

	return 0;

}/* i2c_start */


/*************************************************************************
 Issues a start condition and sends address and transfer direction.
 If device is busy, use ack polling to wait until device is ready
 
 Input:   address and transfer direction of I2C device
*************************************************************************/
void I2C_Start_Wait(unsigned char address)
{
    uint8_t   twst;


    while ( 1 )
    {
	    // send START condition
	    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    
    	// wait until transmission completed
    	while(!(TWCR & (1<<TWINT)));
    
    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;
    	if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
    
    	// send device address
    	TWDR = address;
    	TWCR = (1<<TWINT) | (1<<TWEN);
    
    	// wail until transmission completed
    	while(!(TWCR & (1<<TWINT)));
    
    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;
    	if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) ) 
    	{    	    
    	    /* device busy, send stop condition to terminate write operation */
	        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	        
	        // wait until stop condition is executed and bus released
	        while(TWCR & (1<<TWSTO));
	        
    	    continue;
    	}
    	//if( twst != TW_MT_SLA_ACK) return 1;
    	break;
     }

}/* I2C_Start_Wait */


/*************************************************************************
 Issues a repeated start condition and sends address and transfer direction 

 Input:   address and transfer direction of I2C device
 
 Return:  0 device accessible
          1 failed to access device
*************************************************************************/
unsigned char I2C_Repeated_Start(unsigned char address)
{
    return i2c_start( address );

}/* I2C_Repeated_Start */


/*************************************************************************
 Terminates the data transfer and releases the I2C bus
*************************************************************************/
void I2C_Stop(void)
{
    /* send stop condition */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
	// wait until stop condition is executed and bus released
	while(TWCR & (1<<TWSTO));

}/* I2C_Stop */


/*************************************************************************
  Send one byte to I2C device
  
  Input:    byte to be transfered
  Return:   0 write successful 
            1 write failed
*************************************************************************/
unsigned char I2C_Write( unsigned char data )
{	
    uint8_t   twst;
    
	// send data to the previously addressed device
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;

}/* I2C_Write */


/*************************************************************************
 Read one byte from the I2C device, request more data from device 
 
 Return:  byte read from I2C device
*************************************************************************/
unsigned char I2C_Read_Ack(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));    

    return TWDR;

}/* I2C_Read_Ack */


/*************************************************************************
 Read one byte from the I2C device, read is followed by a stop condition 
 
 Return:  byte read from I2C device
*************************************************************************/
unsigned char I2C_Read_Nack(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
    return TWDR;

}/* I2C_Read_Nack */
