/*
 * LM35.h
 *
 * Created: 3/1/2023 10:51:34 PM
 *  Author: dell
 */ 


#ifndef LM35_H_
#define LM35_H_

#include "../../MCAL/ADC/ADC_Interface.h"

#define V_REFERENCE (5)
#define LM_CH ADC_CH_1

void LM35_init();
uint8 LM35_read();

#endif /* LM35_H_ */