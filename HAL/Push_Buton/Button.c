/*
 * Button.c
 *
 * Created: 3/16/2023 8:40:41 PM
 *  Author: dell
 */ 


#include "Button.h"


void button_with_INT_init(interrupt_callback_t button_ISR){
	register_EX2(button_ISR);
	EXT_INT_Init();
	EXT_INT_SET_CONFIG();
}

