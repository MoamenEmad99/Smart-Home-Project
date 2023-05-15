/*
 * LM35.c
 *
 * Created: 3/1/2023 10:51:54 PM
 *  Author: dell
 */ 

#include "LM35.h"


void LM35_init(){
	ADC_init(LM_CH);
}

uint8 LM35_read(){
	return(((float)ADC_read(LM_CH)/1023)*V_REFERENCE*100);
}

