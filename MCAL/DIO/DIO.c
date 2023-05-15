/*
 * DIO.c
 *
 * Created: 2/17/2023 7:32:53 PM
 *  Author: dell
 */ 

#include "DIO_Interface.h"



void DIO_vSetPinDirection(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber, uint8 copy_u8state){
	switch(Copy_u8PORT)
	{
		case PORT_A:
			if(copy_u8state==IN)
			{
				clearbit(PORTA_BASE->DDR, Copy_u8PinNumber);
				break;
			}
			else if(copy_u8state==OUT)
			{
				setbit(PORTA_BASE->DDR, Copy_u8PinNumber);
				break;	
			}
			else if(copy_u8state==IN_PULLUP)
			{
				clearbit(PORTA_BASE->DDR, Copy_u8PinNumber);
				setbit(PORTA_BASE->Port, Copy_u8PinNumber);
				break;
			}

		case PORT_B:
			if(copy_u8state==IN)
			{
				clearbit(PORTB_BASE->DDR, Copy_u8PinNumber);
				break;
			}
			else if(copy_u8state==OUT)
			{
				setbit(PORTB_BASE->DDR, Copy_u8PinNumber);
				break;
			}
			else if(copy_u8state==IN_PULLUP)
			{
				clearbit(PORTB_BASE->DDR, Copy_u8PinNumber);
				setbit(PORTB_BASE->Port, Copy_u8PinNumber);
				break;
			}

		case PORT_C:
			if(copy_u8state==IN)
			{
				clearbit(PORTC_BASE->DDR, Copy_u8PinNumber);
				break;
			}
			else if(copy_u8state==OUT)
			{
				setbit(PORTC_BASE->DDR, Copy_u8PinNumber);
				break;
			}
			else if(copy_u8state==IN_PULLUP)
			{
				clearbit(PORTC_BASE->DDR, Copy_u8PinNumber);
				setbit(PORTC_BASE->Port, Copy_u8PinNumber);
				break;
			}

		case PORT_D:
			if(copy_u8state==IN)
			{
				clearbit(PORTD_BASE->DDR, Copy_u8PinNumber);
				break;
			}
			else if(copy_u8state==OUT)
			{
				setbit(PORTD_BASE->DDR, Copy_u8PinNumber);
				break;
			}
			else if(copy_u8state==IN_PULLUP)
			{
				clearbit(PORTD_BASE->DDR, Copy_u8PinNumber);
				setbit(PORTD_BASE->Port, Copy_u8PinNumber);
				break;
			}	
		
	}
}
		
	
void DIO_vWritePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber, uint8 Copy_u8value){
	switch(Copy_u8PORT)
	{
		case PORT_A:
			if(Copy_u8value==LOW)
			{
				clearbit(PORTA_BASE->Port, Copy_u8PinNumber);
				break;
			}
			else if(Copy_u8value==HIGH)
			{
				setbit(PORTA_BASE->Port, Copy_u8PinNumber);
				break;
			}
			else
			{
				//Error
				break;
			}

		case PORT_B:
			if(Copy_u8value==LOW)
			{
				clearbit(PORTB_BASE->Port, Copy_u8PinNumber);
				break;
			}
			else if(Copy_u8value==HIGH)
			{
				setbit(PORTB_BASE->Port, Copy_u8PinNumber);
				break;
			}
			else
			{
				//Error
				break;
			}

		case PORT_C:
			if(Copy_u8value==LOW)
			{
				clearbit(PORTC_BASE->Port, Copy_u8PinNumber);
				break;
			}
			else if(Copy_u8value==HIGH)
			{
				setbit(PORTC_BASE->Port, Copy_u8PinNumber);
				break;
			}
			else
			{
				//Error
				break;
			}

		case PORT_D:
			if(Copy_u8value==LOW)
			{
				clearbit(PORTD_BASE->Port, Copy_u8PinNumber);
				break;
			}
			else if(Copy_u8value==HIGH)
			{
				setbit(PORTD_BASE->Port, Copy_u8PinNumber);
				break;
			}
			else
			{
				//Error
				break;
			}
		
	}
}
	

void DIO_vTogglePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber){
	switch(Copy_u8PORT)
	{
		case PORT_A:
			togglebit(PORTA_BASE->Port, Copy_u8PinNumber);
			break;

		case PORT_B:
			togglebit(PORTB_BASE->Port, Copy_u8PinNumber);
			break;
			
		case PORT_C:
			togglebit(PORTC_BASE->Port, Copy_u8PinNumber);
			break;
			
		case PORT_D:
			togglebit(PORTD_BASE->Port, Copy_u8PinNumber);
			break;
	}
}
	
	
void DIO_vSetPortDirection(uint8 Copy_u8PORT, uint8 copy_u8state){
	switch(Copy_u8PORT)
	{
		case PORT_A:
			if(copy_u8state==IN) PORTA_BASE->DDR = 0x00;
			else if(copy_u8state==OUT) PORTA_BASE->DDR = 0xFF;
			else if(copy_u8state==IN_PULLUP){
				PORTA_BASE->DDR = 0xFF;
				PORTA_BASE->Port = 0xFF;
			}
			break;
			
		case PORT_B:
			if(copy_u8state==IN) PORTB_BASE->DDR = 0x00;
			else if(copy_u8state==OUT) PORTB_BASE->DDR = 0xFF;
			else if(copy_u8state==IN_PULLUP){
				PORTB_BASE->DDR = 0xFF;
				PORTB_BASE->Port = 0xFF;
			}
			break;
			
		case PORT_C:
			if(copy_u8state==IN) PORTC_BASE->DDR = 0x00;
			else if(copy_u8state==OUT) PORTC_BASE->DDR = 0xFF;
			else if(copy_u8state==IN_PULLUP){
				PORTC_BASE->DDR = 0xFF;
				PORTC_BASE->Port = 0xFF;
			}
			break;
			
		case PORT_D:
			if(copy_u8state==IN) PORTD_BASE->DDR = 0x00;
			else if(copy_u8state==OUT) PORTD_BASE->DDR = 0xFF;
			else if(copy_u8state==IN_PULLUP){
				PORTD_BASE->DDR = 0xFF;
				PORTD_BASE->Port = 0xFF;
			}
			break;
	}
}
	
	
void DIO_vWritePort(uint8 Copy_u8PORT, uint8 Copy_u8value){
	switch(Copy_u8PORT)
	{
		case PORT_A:
			if(Copy_u8value==LOW) PORTA_BASE->Port = 0x00;
			else if(Copy_u8value==HIGH) PORTA_BASE->Port = 0xFF;
			break;
			
		case PORT_B:
			if(Copy_u8value==LOW) PORTB_BASE->Port = 0x00;
			else if(Copy_u8value==HIGH) PORTB_BASE->Port = 0xFF;
			break;
			
		case PORT_C:
			if(Copy_u8value==LOW) PORTC_BASE->Port = 0x00;
			else if(Copy_u8value==HIGH) PORTC_BASE->Port = 0xFF;
			break;
			
		case PORT_D:
			if(Copy_u8value==LOW) PORTD_BASE->Port = 0x00;
			else if(Copy_u8value==HIGH) PORTD_BASE->Port = 0xFF;
			break;
	}
}
	
	
uint8 DIO_u8GetPinValue(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber){
	switch(Copy_u8PORT)
	{
		case PORT_A:
			return getbit((PORTA_BASE->Pin), Copy_u8PinNumber);
			break;
			
		case PORT_B:
			return getbit((PORTB_BASE->Pin), Copy_u8PinNumber);
			break;
			
		case PORT_C:
			return getbit((PORTC_BASE->Pin), Copy_u8PinNumber);
			break;
			
		case PORT_D:
			return getbit((PORTD_BASE->Pin), Copy_u8PinNumber);
			break;
	}
}


uint8 DIO_u8GetPortValue(uint8 Copy_u8PORT){
	switch(Copy_u8PORT)
	{
		case PORT_A:
			return (PORTA_BASE->Pin);
			break;
			
		case PORT_B:
			return (PORTB_BASE->Pin);
			break;
			
		case PORT_C:
			return (PORTC_BASE->Pin);
			break;
			
		case PORT_D:
			return (PORTD_BASE->Pin);
			break;
	}
}


void DIO_vTogglesPort(uint8 Copy_u8PORT){
	switch(Copy_u8PORT)
	{
		case PORT_A:
			PORTA_BASE->Port ^= 0xFF;
			break;
			
		case PORT_B:
			PORTB_BASE->Port ^= 0xFF;
			break;
			
		case PORT_C:
			PORTC_BASE->Port ^= 0xFF;
			break;
			
		case PORT_D:
			PORTD_BASE->Port ^= 0xFF;
			break;
	}
}


void DIO_vWritePortValue(uint8 Copy_u8PORT, uint8 Copy_u8value){
	switch(Copy_u8PORT)
	{
		case PORT_A:
			PORTA_BASE->Port = Copy_u8value;
			break;
			
		case PORT_B:
			PORTB_BASE->Port = Copy_u8value;
			break;
			
		case PORT_C:
			PORTC_BASE->Port = Copy_u8value;
			break;
			
		case PORT_D:
			PORTD_BASE->Port = Copy_u8value;
			break;
	}
}