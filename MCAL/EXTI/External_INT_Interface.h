/*
 * External_INT.h
 *
 * Created: 2/18/2023 11:40:37 AM
 *  Author: dell
 */ 


#ifndef EXTERNAL_INT_H_
#define EXTERNAL_INT_H_

#include "../../LIB/Calcbit.h"
#include "../../LIB/Datatypes.h"
#include "External_INT_Reg.h"


/************* Modes ***********************/
// Modes that will be used for the external interrupt configuration
#define LOW_LEVEL_MODE 0
#define FALLING_EDGE_MODE 1
#define RISING_EDGE_MODE 2
#define FALLING_AND_RISING_EDGE_MODE 3
/********** Enable Ext Interrupts ***********/
#define ENABLE_INT0 6
#define ENABLE_INT1 7
#define ENABLE_INT2 5
#define DISABLE_INT 0

/********************************************/
#define Pin_Int0 2
#define Pin_Int1 3
#define Pin_Int2 2
#define GIE 7
//Struct that contains the external interrupt configuration options.
typedef struct
{
	uint8 Enable_INT0_Interrupt;
	uint8 Enable_INT1_Interrupt;
	uint8 Enable_INT2_Interrupt;
	uint8 INT0_Triggering_Mode;
	uint8 INT1_Triggering_Mode;
	uint8 INT2_Triggering_Mode;
}EXT_Int_Conf;


//External interrupt configs
static EXT_Int_Conf INT = {
	ENABLE_INT0,
	ENABLE_INT1,
	ENABLE_INT2,
	FALLING_AND_RISING_EDGE_MODE,
	FALLING_AND_RISING_EDGE_MODE,
	FALLING_EDGE_MODE
};




//external interrupt request 0
#define EXT_INT_0 __vector_1
//external interrupt request 1
#define EXT_INT_1 __vector_2
//external interrupt request 2
#define EXT_INT_2 __vector_3

//ISR macro
#define ISR(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used)); \
void INT_VECT(void)


//pointer to function typedef (for isr callback)
typedef void (*interrupt_callback_t) (void);

/*********** External_Interrupt APIS ****************/
void EXT_INT_Init(void);
void EXT_INT_SET_CONFIG(void);
void register_EX0(interrupt_callback_t callback0);
void register_EX1(interrupt_callback_t callback1);
void register_EX2(interrupt_callback_t callback2);
void disable_interrupt(uint8 );
void enable_interrupt(uint8);

#endif /* EXTERNAL_INT_H_ */