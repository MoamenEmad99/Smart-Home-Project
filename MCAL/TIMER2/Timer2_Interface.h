/*
 * Timer0_Interface.h
 *
 * Created: 2/24/2023 1:36:10 PM
 *  Author: dell
 */ 


#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

#include "../../LIB/Calcbit.h"
#include "../../LIB/Datatypes.h"
#include "Timer2_Reg.h"

//Timer2 operating modes
#define NORMAL_MODE (0)
#define PWM_PHASE_CORRECT (1)
#define CTC_MODE (2)
#define FAST_PWM (3)

//prescaler masks
#define PRESCALER_CLEAR (0xF8)
#define PRESCALER_1 (0x01)
#define PRESCALER_8 (0x02)
#define PRESCALER_64 (0x03)
#define PRESCALER_256 (0x04)
#define PRESCALER_1024 (0x05)
#define EXT_CLK_FALLING_EDGE (0x06)
#define EXT_CLK_RISING_EDGE (0x07)

//Timer2 interrupt state
#define TIMER2_INT_DISABLE (0)
#define TIMER2_INT_ENABLE (1)


/*** Timer2 APIs***/
 void TIMER2_SetConfig(void); void TIMER2_DelayMilliSeconds_with_Blocking(uint16 Milli_Seconds); void TIMER2_DelayMicroSeconds_with_Blocking(uint16 Micro_Seconds);//pointer to function typedef (for isr callback)typedef void (*interrupt_callback_t) (void);

//Timer configs struct
typedef struct
{
	uint8 Mode;
	uint8 Enable_Interrupt;	
}Timer_Config2;

//Timer2 configs object
static Timer_Config2 Config2 = {
	CTC_MODE,
	TIMER2_INT_DISABLE,
	};

//TIMER2 overflow interrupt request
#define TIMER2_OV_INT __vector_5
//TIMER2 compare match interrupt request
#define TIMER2_COMP_INT __vector_4

//ISR macro
#define ISR(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used)); \
void INT_VECT(void)

#endif /* TIMER0_INTERFACE_H_ */
