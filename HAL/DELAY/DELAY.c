/*
 * DELAY.c
 *
 * Created: 3/9/2023 1:17:39 AM
 *  Author: dell
 */ 

#include "../../MCAL/TIMER2/Timer2_Interface.h"

void delayMilliSeconds(uint16 Milliseconds){
	TIMER2_DelayMilliSeconds_with_Blocking(Milliseconds);
}

void delayMicroSeconds(uint16 Microseconds){
	TIMER2_DelayMilliSeconds_with_Blocking(Microseconds);
}