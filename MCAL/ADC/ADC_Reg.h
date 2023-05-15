/*
 * ADC_Reg.h
 *
 * Created: 3/1/2023 3:10:35 PM
 *  Author: dell
 */ 


#ifndef ADC_REG_H_
#define ADC_REG_H_

#define SFIOR (*(volatile uint8*)(0x50))
#define ADMUX (*(volatile uint8*)(0x27))
#define ADCSRA (*(volatile uint8*)(0x26))
#define ADC (*(volatile uint16*)(0x24))
#define DDRA (*(volatile uint8*)(0x3A))

#define ADMUX_ADLAR 5
#define ADMUX_REFS0 6
#define ADMUX_REFS1 7

#define ADCSRA_ADIE 3 
#define ADCSRA_ADIF 4
#define ADCSRA_ADATE 5
#define ADCSRA_ADSC 6
#define ADCSRA_ADEN 7









#endif /* ADC_REG_H_ */