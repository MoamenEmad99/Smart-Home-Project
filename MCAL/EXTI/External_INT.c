/*
 * External_INT.c
 *
 * Created: 2/18/2023 11:40:48 AM
 *  Author: dell
 */ 


#include "External_INT_Interface.h"


/*********** External_Interrupt APIS ****************/

//sets the directions of the enabled interrupts to input
void EXT_INT_Init(void){
	if(INT.Enable_INT0_Interrupt != DISABLE_INT)
		clearbit(DDRD, Pin_Int0);

	if(INT.Enable_INT1_Interrupt != DISABLE_INT)
		clearbit(DDRD, Pin_Int1);
		
	if(INT.Enable_INT2_Interrupt != DISABLE_INT){
		clearbit(DDRB, Pin_Int2);
		setbit(PORTB,Pin_Int2);
	}
		
}

//sets the configs of the ext. interrupts to the control registers
void EXT_INT_SET_CONFIG(void)
{	
	setbit(SREG, GIE); //enable global interrupt
	
	if(INT.Enable_INT0_Interrupt != DISABLE_INT){
		setbit(GICR, ENABLE_INT0); //enable INT0
		//set triggering mode
		switch(INT.INT0_Triggering_Mode){
			case LOW_LEVEL_MODE:
				clearbit(MCUCR, 0);
				clearbit(MCUCR, 1);
				break;
				
			case FALLING_AND_RISING_EDGE_MODE:
				setbit(MCUCR, 0);
				clearbit(MCUCR, 1);
				break;
				
			case FALLING_EDGE_MODE:
				clearbit(MCUCR, 0);
				setbit(MCUCR, 1);
				break;
				
			case RISING_EDGE_MODE:
				setbit(MCUCR, 0);
				setbit(MCUCR, 1);
				break;	
		}
	}

	if(INT.Enable_INT1_Interrupt != DISABLE_INT){
		setbit(GICR, ENABLE_INT1); //enable INT1
		//set triggering mode
		switch(INT.INT1_Triggering_Mode){
			case LOW_LEVEL_MODE:
			clearbit(MCUCR, 2);
			clearbit(MCUCR, 3);
			break;
			
			case FALLING_AND_RISING_EDGE_MODE:
			setbit(MCUCR, 2);
			clearbit(MCUCR, 3);
			break;
			
			case FALLING_EDGE_MODE:
			clearbit(MCUCR, 2);
			setbit(MCUCR, 3);
			break;
			
			case RISING_EDGE_MODE:
			setbit(MCUCR, 2);
			setbit(MCUCR, 3);
			break;
		}
	}
	
	if(INT.Enable_INT2_Interrupt != DISABLE_INT){
		setbit(GICR, ENABLE_INT2); //enable INT2
		//set triggering mode
		switch(INT.INT2_Triggering_Mode){
			case FALLING_EDGE_MODE:
			clearbit(MCUCSR, 6);
			break;
			
			case RISING_EDGE_MODE:
			setbit(MCUCSR, 6);
			break;
		}
	}
	
}


//pointers to callback functions
interrupt_callback_t INT0_callback = NULL;
interrupt_callback_t INT1_callback = NULL;
interrupt_callback_t INT2_callback = NULL;

//assigning callback functions addresses to the pointers
void register_EX0(interrupt_callback_t callback0){
	
	INT0_callback = callback0;
}

void register_EX1(interrupt_callback_t callback1)
{
	INT1_callback = callback1;
}

void register_EX2(interrupt_callback_t callback2)
{
	INT2_callback = callback2;
}

//interrupt service routine for INT0
ISR(EXT_INT_0){
	if(INT0_callback != NULL)
		INT0_callback();
}

//interrupt service routine for INT1
ISR(EXT_INT_1){
	if(INT1_callback != NULL)
		INT1_callback();
}

//interrupt service routine for INT2
ISR(EXT_INT_2){
	if(INT2_callback != NULL)
		INT2_callback();
}

void disable_interrupt(uint8  inter){
switch (inter){
    case 0 :
	    clearbit(GICR, ENABLE_INT0);
        break;
		
	case 1:
	clearbit(GICR, ENABLE_INT1);
        break;
   
    case 2:
	clearbit(GICR, ENABLE_INT2);
      break;

}	
	
}


void enable_interrupt(uint8 interupt_t){
	switch (interupt_t){
		case 0 :
		setbit(GICR, ENABLE_INT0);
		break;
		
		case 1:
		setbit(GICR, ENABLE_INT1);
		break;
		
		case 2:
		setbit(GICR, ENABLE_INT2);
		break;

	}
	
	
	
}