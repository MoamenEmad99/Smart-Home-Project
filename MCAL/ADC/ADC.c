/*
 * ADC.c
 *
 * Created: 3/1/2023 3:11:15 PM
 *  Author: dell
 */ 

#include "ADC_Interface.h"


void ADC_init(uint8 ADC_CH){
	//set pin to input
	clearbit(DDRA, ADC_CH);
	
	//reseting registers to 0
	ADMUX = 0x00;
	ADCSRA = 0x00;
	
	//selecting reference voltage
	switch(ADC_conf.VREF){
		//AREF, Internal Vref turned off
		case AREF:
			clearbit(ADMUX,ADMUX_REFS0);
			clearbit(ADMUX, ADMUX_REFS1);
			break;
		
		//AVCC with external capacitor at AREF pin	
		case AVCC:
			setbit(ADMUX,ADMUX_REFS0);
			clearbit(ADMUX, ADMUX_REFS1);
			break;
		
		//Internal 2.56V Voltage Reference with external capacitor at AREF pin	
		case INTERNAL:
			setbit(ADMUX,ADMUX_REFS0);
			setbit(ADMUX, ADMUX_REFS1);
			break;
	}
	
	//setting adjust mode
	if(ADC_conf.Adjust == LEFT) setbit(ADMUX,ADMUX_ADLAR);
	else if(ADC_conf.Adjust == RIGHT) clearbit(ADMUX,ADMUX_ADLAR);
	
	//Enable ADC
	setbit(ADCSRA,ADCSRA_ADEN);	
	
	//Setting prescaler
	ADCSRA = (ADCSRA & 0xF8) | ADC_conf.Prescaler;
	
	//Setting interrupt mode
	if(ADC_conf.Interrupt == INTERRUPT_DISABLE) clearbit(ADCSRA,ADCSRA_ADIE);
	else if(ADC_conf.Interrupt == INTERRUPT_ENABLE) setbit(ADCSRA,ADCSRA_ADIE);
	
	//Setting auto trigger mode
	if(ADC_conf.Auto_trigger == AUTO_TRIGGER_DISABLE) clearbit(ADCSRA,ADCSRA_ADATE);
	else if(ADC_conf.Auto_trigger == AUTO_TRIGGER_ENABLE) setbit(ADCSRA,ADCSRA_ADATE);
}

uint16 ADC_read(uint8 ADC_CH){
	//selecting ADC channel
	ADMUX = (ADMUX & 0xE0) | ADC_CH;
	
	//start ADC conversion
	setbit(ADCSRA,ADCSRA_ADSC);
	
	//busy wait until conversion completes
	while(getbit(ADCSRA,ADCSRA_ADIF)==0);
	
	if(ADC_conf.Adjust == LEFT) return (ADC>>6);
	else if(ADC_conf.Adjust == RIGHT) return (ADC);
}