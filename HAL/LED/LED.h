/*
 * LED.h
 *
 * Created: 3/15/2023 1:06:51 PM
 *  Author: dell
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../LIB/Datatypes.h"

#define RED_LED		PORT_B, PIN7
#define YEL_LED		PORT_A, PIN6
#define BLU_LED		PORT_A, PIN5
#define GRN_LED		PORT_A, PIN4

void LED_init(uint8 LED_port, uint8 LED_pin);
void LED_on(uint8 LED_port, uint8 LED_pin);
void LED_off(uint8 LED_port, uint8 LED_pin);
void LED_toggle(uint8 LED_port, uint8 LED_pin);
void LED_blink(uint8 LED_port, uint8 LED_pin, uint8 delay, uint8 times);







#endif /* LED_H_ */