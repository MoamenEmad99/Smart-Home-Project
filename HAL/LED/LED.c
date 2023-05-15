/*
 * LED.c
 *
 * Created: 3/15/2023 1:07:09 PM
 *  Author: dell
 */ 

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/TIMER2/Timer2_Interface.h"
#include "LED.h"

void LED_init(uint8 LED_port, uint8 LED_pin){
	DIO_vSetPinDirection(LED_port, LED_pin, OUT);
}

void LED_on(uint8 LED_port, uint8 LED_pin){
	DIO_vWritePin(LED_port, LED_pin, HIGH);
}

void LED_off(uint8 LED_port, uint8 LED_pin){
	DIO_vWritePin(LED_port, LED_pin, LOW);
}

void LED_toggle(uint8 LED_port, uint8 LED_pin){
	DIO_vTogglePin(LED_port, LED_pin);
}

void LED_blink(uint8 LED_port, uint8 LED_pin, uint8 delay, uint8 times){
	for(uint8 i=0; i<times; i++){
		DIO_vWritePin(LED_port, LED_pin, HIGH);
		TIMER0_DelayMilliSeconds_with_Blocking(delay);
		DIO_vWritePin(LED_port, LED_pin, LOW);
		TIMER0_DelayMilliSeconds_with_Blocking(delay);		
	}
}