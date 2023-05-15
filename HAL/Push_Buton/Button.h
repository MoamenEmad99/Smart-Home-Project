/*
 * Button.h
 *
 * Created: 3/16/2023 8:40:29 PM
 *  Author: dell
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
 	
#include "../../MCAL/EXTI/External_INT_Interface.h"

void button_with_INT_init(interrupt_callback_t button_ISR);


#endif /* BUTTON_H_ */