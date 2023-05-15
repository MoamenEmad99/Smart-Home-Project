/*
 * I2C.c
 *
 *  Created on: Mar 8, 2023
 *      Author: abdelrahman
 */
#include"data_types_i2c.h"


#include "../../LIB/Datatypes.h"
#include "../../LIB/Calcbit.h"
#include "I2C_HW.h"
#include "I2C_config.h"


void init_I2C(void){

//set division_facto
IC_ACCESS->TWSR_R = 0x00;
IC_ACCESS->TWBR_R = 72;
//set the prescalar
}

uint8 START_I2C(uint8 slave){

uint8 state;	

IC_ACCESS->TWCR_R = ((1u<<TWSTA_bit)|(1u<<TWEN_bit)|(1u<<TWINT_bit)) ; // clear interrupt flag , start bit , enable module
while(!(IC_ACCESS->TWCR_R&(1u<<TWINT_bit)));                               // waite untile finish current job

state = ((IC_ACCESS->TWSR_R)&(TW_status_mask));                                 //read the status

if(state != 0x08){
return 0;
}

IC_ACCESS->TWDR_R = slave;
IC_ACCESS->TWCR_R = (1u<<TWEN_bit)|(1u<<TWINT_bit);                         //enable module , clear the flag

while(!(IC_ACCESS->TWCR_R&(1u<<TWINT_bit)));   

state = ((IC_ACCESS->TWSR_R)&(TW_status_mask));   

if(state == 0x18 )
{ return  1;                           }

if(state == 0x20)
{  return  2 ;                          }

else

{return 3; }

}


uint8 repeated_start(uint8 slave){

uint8 state;

	IC_ACCESS->TWCR_R =((1u<<TWSTA_bit)|(1u<<TWEN_bit)|(1u<<TWINT_bit)) ; // clear interrupt flag , start bit , enable module
	while(!((IC_ACCESS->TWCR_R)&(1u<<TWINT_bit)));                               // waite untile finish current job

	state = ((IC_ACCESS->TWSR_R)&(TW_status_mask));                                 //read the status

	if(state != 0x10){
		return 0;
	}

	IC_ACCESS->TWDR_R = slave;
	IC_ACCESS->TWCR_R = (1u<<TWEN_bit)|(1u<<TWINT_bit);                         //enable module , clear the flag

	while(!(IC_ACCESS->TWCR_R&(1u<<TWINT_bit)));

	state = (IC_ACCESS->TWSR_R&TW_status_mask);

	if(state == 0x40 )
	{ return  1;                           }

	if(state == 0x48)
	{  return  2 ;                          }

	else

	{return 3 ; }	
	}	

uint8  write_I2C(uint8 data){
	
	uint8 state ;
	IC_ACCESS->TWDR_R = data;
	IC_ACCESS->TWCR_R = ((1u<<TWEN_bit)|(1u<<TWINT_bit));      // enable twi , clear the flag
	
	while(!(IC_ACCESS->TWCR_R&(1u<<TWINT_bit)));       
	
	state = (IC_ACCESS->TWSR_R & TW_status_mask);
	
	if(state == 0x28)
	{return 0;          }
	
	if(state == 0x30)
	{return  1;         }
     
     else
    {
		return 2 ;
	}

}


uint8 read_ack(){
	IC_ACCESS->TWCR_R = ((1u<<TWEN_bit)|(1u<<TWINT_bit)|(1u<<TWEA_bit));
	while(!(IC_ACCESS->TWCR_R & (1u<<TWINT_bit)));
	return (IC_ACCESS->TWDR_R);
}


void stop_I2C(){
	IC_ACCESS->TWCR_R = ((1u<<TWSTO_bit) | (1u<<TWINT_bit) | (1u<<TWEN_bit));
	while(IC_ACCESS->TWCR_R&(1u<<TWSTO_bit));
	
	
}



uint8 read_nack(){
	IC_ACCESS->TWCR_R = ((1u<<TWEN_bit)|(1u<<TWINT_bit));
	while(!(IC_ACCESS->TWCR_R&(1u<<TWINT_bit)));
	return (IC_ACCESS->TWDR_R);
}



void I2C_Slave_Init(uint8 slave_address){
	
	IC_ACCESS->TWBR_R = 0x00;
	IC_ACCESS->TWSR_R = 0x00;
	
	IC_ACCESS->TWAR_R = slave_address;
	IC_ACCESS->TWCR_R = ((1u<<TWEN_bit)|(1u<<TWEA_bit));
	
	}
	
uint8 I2C_Slave_Listen(){
		
		

		while(1){
uint8 state;
			while(!(IC_ACCESS->TWCR_R & (1u<<TWINT_bit)));
										
			state  = (IC_ACCESS->TWSR_R&TW_status_mask);
			
			if(state==0x60||state==0x68)         //adress + w
			{
				
				return 0;
			}
			
			if(state==0xA8||state==0xB0)        //adrss + r
			{
				return 1;
			}
			if(state==0x70||state==0x78)           //adress +general call
			{
				return 2;
			}
			else
			continue;
		}
	}
	
	
int I2C_Slave_Transmit(uint8 data)
	{
		uint8 status;
		IC_ACCESS->TWDR_R = data;			                          /* Write data to TWDR to be transmitted */
		IC_ACCESS->TWCR_R = ((1<<TWEN_bit)|(1<<TWINT_bit)|(1<<TWEA_bit));    /* Enable TWI & clear interrupt flag */
		while(!(IC_ACCESS->TWCR_R & (1<<TWINT_bit)));	                                      /* Wait until TWI finish its current job */
		status=(IC_ACCESS->TWSR_R & TW_status_mask);		                                           /* Read TWI status register */
		if(status==0xA0)		                                          /* Check for STOP/REPEATED START received */
		{
			IC_ACCESS->TWCR_R |= (1<<TWINT_bit);	                                          /* Clear interrupt flag & return -1 */
			return -1;
		}
		if(status==0xB8)                    		                      /* Check for data transmitted &ack received */
		return 0;			                                               /* If yes then return 0 */
		if(status==0xC0)		                                           /* Check for data transmitted &nack received */
		{
			IC_ACCESS->TWCR_R|=(1<<TWINT_bit);                   	                       /*  Clear interrupt flag & return -2 */
			return -2;
		}
		if(status==0xC8)		                                           /* Last byte transmitted with ack received */
		return -3;			                                              /* If yes then return -3 */
		else	                            	                         	/* else return -4 */
		return -4;
	}

char I2C_Slave_Receive()
{
	uint8      status;	                     	                             /* Declare variable */
	IC_ACCESS->TWCR_R = ((1<<TWEN_bit)|(1<<TWEA_bit)|(1<<TWINT_bit)); 
	while(!(IC_ACCESS->TWCR_R & (1<<TWINT_bit)));
	                                                                                               /* Enable TWI & generation of ack */		                                                                            /* Wait until TWI finish its current job */
	status= (IC_ACCESS->TWSR_R & TW_status_mask);	                                                   	/* Read TWI status register */
	if(status==0x80||status==0x90)
	 {                                                                                       /* Check for data received &ack returned */
	return (IC_ACCESS->TWDR_R);		                                                     /* If yes then return received data */
	}
	                                                                      
   if(status==0x88||status==0x98){							               /*  Check for data received, nack returned & switched to not addressed slave mode */
    return (IC_ACCESS->TWDR_R);	
	}
		                                                     /*  If yes then return received data */
	if(status==0xA0)		                                                 /* Check wether STOP/REPEATED START */
	{
		IC_ACCESS->TWCR_R |= (1<<TWINT_bit);	                                               /* Clear interrupt flag & return -1 */
		return -1;
	}
	else
	return -2;			                                                     /* Else return -2 */
}

void slave_stop(){
	setbit(IC_ACCESS->TWCR_R , TWINT_bit);
	uint8 status;
while(!(IC_ACCESS->TWCR_R & (1<<TWINT_bit)));
                                                  /* Enable TWI & generation of ack */		                                                                            /* Wait until TWI finish its current job */
status= (IC_ACCESS->TWSR_R & TW_status_mask);	
	if(status == 0xA0 ){
		setbit(IC_ACCESS->TWCR_R , TWINT_bit);
		
	}
	
	
}