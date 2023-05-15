/*
 * FAN.c
 *
 * Created: 3/17/2023 2:27:12 PM
 *  Author: dell
 */ 


#include "FAN.h"

void FAN_init(){
	DIO_vSetPinDirection(EN, OUT);
	DIO_vWritePin(EN, LOW);		
}

void FAN_Rotate(uint8 State){
	//set motor state to on
	if (State == ON_STATE)
	{
		DIO_vWritePin(EN, HIGH);
	}

	//set motor State to off
	else if (State == OFF_STATE)
	{
		DIO_vWritePin(EN, LOW);
	}

}