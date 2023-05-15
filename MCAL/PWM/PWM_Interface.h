/*
 * PWM_Interface.h
 *
 * Created: 2/25/2023 8:32:38 PM
 *  Author: dell
 */ 


#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

#include "../../LIB/Datatypes.h"

//PWM Mode and Polarity Select
#define PWM_MODULATION_MODE  PHASE_CORRECT_MODE
#define CHANNEL_A_POLARITY	 NON_INVERTING
#define CHANNEL_B_POLARITY   NON_INVERTING

//PWM Modes and Polarities
#define FAST_PWM_MODE (14)
#define PHASE_CORRECT_MODE (8)
#define CHANNEL_DISABLE (0)
#define NON_INVERTING (2)
#define INVERTING (3)
	
//Prescaler masks
#define PRESCALER_CLEAR (0xF8)
#define PRESCALER_1 (0x01)
#define PRESCALER_8 (0x02)
#define PRESCALER_64 (0x03)
#define PRESCALER_256 (0x04)
#define PRESCALER_1024 (0x05)
#define EXT_CLK_FALLING_EDGE (0x06)
#define EXT_CLK_RISING_EDGE (0x06)


#define MAX_TOP (0x10000)


#define CHANNEL_A_PIN (5)
#define CHANNEL_B_PIN (4)


static void PWM_Start(uint16 prescalar);

void PWM_Stop(void);

void PWM_Init();

void PWM_Generate_CHANNELA(uint8 Copy_u8DutyCycle,uint32 Copy_u32freq);

void PWM_Generate_CHANNELB(uint8 Copy_u8DutyCycle,uint32 Copy_u32freq);

#endif /* PWM_INTERFACE_H_ */