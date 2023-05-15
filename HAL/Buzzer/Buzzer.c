/*
 * Buzzer.c
 *
 * Created: 3/12/2023 1:05:24 PM
 *  Author: dell
 */ 

#include "../../MCAL/TIMER2/Timer2_Interface.h"
#include "Buzzer.h"

void Buzzer_init(void){
	TIMER2_SetConfig();
	DIO_vSetPinDirection(BUZZER_PORT, BUZZER_PIN, OUT);
}


void Buzzer_on(uint16 milliseconds){
	if(milliseconds == 0)
		DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, HIGH);
	
	else{
		DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, HIGH);
		TIMER2_DelayMilliSeconds_with_Blocking(milliseconds);
		DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, LOW);
	}
}


void Buzzer_alert(uint16 milliseconds){
	if (milliseconds == 0)
		DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, HIGH);
		
	else{
		for(uint8 i=0; i<10; i++){
			DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, HIGH);
			TIMER0_DelayMilliSeconds_with_Blocking(milliseconds);
			DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, LOW);
			TIMER0_DelayMilliSeconds_with_Blocking(milliseconds);
		}
	}
}


void Buzzer_off(void){
	DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, LOW);
}