/*
 * ADC_Interface.h
 *
 * Created: 3/1/2023 3:11:02 PM
 *  Author: dell
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "ADC_Reg.h"
#include "../../LIB/Calcbit.h"
#include "../../LIB/Datatypes.h"


//pinNames
#define ADC_CH_0 (0)
#define ADC_CH_1 (1)
#define ADC_CH_2 (2)
#define ADC_CH_3 (3)
#define ADC_CH_4 (4)
#define ADC_CH_5 (5)
#define ADC_CH_6 (6)
#define ADC_CH_7 (7)


//reference voltage
//AREF, Internal Vref turned off
#define AREF (0)

//AVCC with external capacitor at AREF pin
#define AVCC (1)

//Internal 2.56V Voltage Reference with external capacitor at AREF pin
#define INTERNAL (3)

//adjust modes
#define RIGHT (0)
#define LEFT (1)

//prescaler
#define PRESCALER_2 (0x00)
#define PRESCALER_4 (0x02)
#define PRESCALER_8 (0x03)
#define PRESCALER_16 (0x04)
#define PRESCALER_32 (0x05)
#define PRESCALER_64 (0x06)
#define PRESCALER_128 (0x07)

//interrupt modes
#define INTERRUPT_DISABLE (0)
#define INTERRUPT_ENABLE (1)

#define AUTO_TRIGGER_DISABLE (0)
#define AUTO_TRIGGER_ENABLE (1)


//ADC configuration structure typedef
typedef struct {
	uint8 Prescaler;
	uint8 VREF;
	uint8 Adjust;
	uint8 Interrupt;
	uint8 Auto_trigger;
} ADC_Config;

//ADC configuration structure
static ADC_Config ADC_conf = {
	PRESCALER_2,
	AVCC,
	RIGHT,
	INTERRUPT_DISABLE,
	AUTO_TRIGGER_DISABLE
};

void ADC_init(uint8 ADC_CH);
uint16 ADC_read(uint8 ADC_CH);



#endif /* ADC_INTERFACE_H_ */