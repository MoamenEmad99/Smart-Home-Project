/*
 * ultrasonic.c
 *
 * Created: 18/03/2023 03:29:01 ص
 *  Author: aslam
 */ 


#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/TIMER0/Timer0_Interface.h"
#include "../../LIB/Calcbit.h"
#include "../../MCAL/TIMER0/Timer0_Reg.h"               /*the triger is B5 and the echo is D2*/
#include "ultrasonic.h"
#include "../../LIB/Datatypes.h"
#include "../../MCAL/TIMER2/Timer2_Interface.h"



uint8 timer0 =0;                           //hold the value of the timer0   for ultrasonic_0
uint8 timer1 = 0;                          //hold the value of timer0 for ultrasonic_1
uint32 counter = 0;                        // count the numbers of over flow of ultrasonic_0 and 1
//uint32 counter_1 = 0;                    //count the numb of over flow of ultrasonic_1
uint32 distance = 0;                      // calculate the distance of ultrasonic
uint32 distance_1 = 0 ;                //hold distance of 1
float64 duration = 0 ;                     //holds the duration of ultra 0
float32 duration_1 = 0;                    // holds the duration of ultra 0
const  uint32 sound_speed = 343;           //in m/s

void handler_T0(void ){
	counter++;

}

void handler_INT0(void){
	
	if(((PORTD_BASE->Pin)&(1U<<2))){
		TCNT0 = 0x00;
		counter = 0;
		TIMER0_start(PRESCALER_1);
	}

	else
	{
		timer0 = TCNT0;
		TIMER0_stop();
		disable_interrupt(0);
		
	}

}

void handler_INT1(void){
	
	if(((PORTD_BASE->Pin)&(1U<<3))){
		TCNT0 = 0x00;
		counter = 0;
		TIMER0_start(PRESCALER_1);}
		
	else
	{
		timer1 = TCNT0;
		TIMER0_stop();
		disable_interrupt(1);
		
	}
	
}



Ultrasonic_INIT(){
	register_EX0(handler_INT0);
	register_EX1(handler_INT1);
	
	register_callback(handler_T0 );
	
	
	DIO_vSetPinDirection(PORT_C , triger_ultra0 , OUT);              // pin_triger for_ultrasonic_0
	DIO_vSetPinDirection(PORT_D, Echo_ultra0, IN);                          //echo for ultrasonic_1
	
	DIO_vSetPinDirection(PORT_C , triger_ultra1 , OUT);              // pin_triger for_ultrasonic_0
	DIO_vSetPinDirection(PORT_D, Echo_ultra1, IN);                          //echo for ultrasonic_1
	
	TIMER0_SetConfig();
	
	EXT_INT_Init();
	EXT_INT_SET_CONFIG();
}

uint32 Distance_0_cm(){
	enable_interrupt(0);
	DIO_vWritePin(PORT_C, triger_ultra0, HIGH);
	TIMER2_DelayMicroSeconds_with_Blocking(500);
	DIO_vWritePin(PORT_C, triger_ultra0, LOW);
	TIMER2_DelayMilliSeconds_with_Blocking(50);
	
	duration = ((((256UL*counter) + timer0)/16));           // calculate the duration in us
	if(duration >0){
		
	distance = ((sound_speed * duration)/20000);  }         //distance = (speed * time )/2        in cm/s
	
	
return distance;

}

uint32 Distance_1_cm(){
	enable_interrupt(1);
		DIO_vWritePin(PORT_C, triger_ultra1, HIGH);
		TIMER2_DelayMicroSeconds_with_Blocking(500);
		DIO_vWritePin(PORT_C, triger_ultra1, LOW);
		TIMER2_DelayMilliSeconds_with_Blocking(50);
	
	duration_1 = ((((256UL*counter) + timer1)/16)); 
	if(duration_1 >0){
		
	distance_1 = ((sound_speed * duration_1)/20000);  }

return distance_1;	
}