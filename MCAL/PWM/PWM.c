/*
 * PWM.c
 *
 * Created: 2/25/2023 8:32:51 PM
 *  Author: dell
 */ 

#include "../../LIB/Calcbit.h"
#include "../../LIB/Datatypes.h"
#include "PWM_Reg.h"
#include "PWM_Interface.h"


static void PWM_Start(uint16 prescaler){
	switch(prescaler){
		case 1024:
			TCCR1B = (TCCR1B & PRESCALER_CLEAR) | PRESCALER_1024;
			break;
			
		case 256:
			TCCR1B = (TCCR1B & PRESCALER_CLEAR) | PRESCALER_256;
			break;
			
		case 64:
			TCCR1B = (TCCR1B & PRESCALER_CLEAR) | PRESCALER_64;
			break;
			
		case 8:
			TCCR1B = (TCCR1B & PRESCALER_CLEAR) | PRESCALER_8;
			break;
			
		case 1:
			TCCR1B = (TCCR1B & PRESCALER_CLEAR) | PRESCALER_1;
			break;
	}
}


void PWM_Stop(void){
	TCCR1B &= PRESCALER_CLEAR;
}


void PWM_Init(){
#if PWM_MODULATION_MODE == FAST_PWM_MODE
	//Setting PWM Modulation Mode to Fast PWM mode
	clearbit(TCCR1A, TCCR1A_WGM10);
	setbit(TCCR1A, TCCR1A_WGM11);
	setbit(TCCR1B, TCCR1B_WGM12);
	setbit(TCCR1B, TCCR1B_WGM13);
	
#endif
#if PWM_MODULATION_MODE == PHASE_CORRECT_MODE
	//Setting PWM Modulation Mode to Phase and Frequency Correct Mode
	clearbit(TCCR1A, TCCR1A_WGM10);
	clearbit(TCCR1A, TCCR1A_WGM11);
	clearbit(TCCR1B, TCCR1B_WGM12);
	setbit(TCCR1B, TCCR1B_WGM13);		
#endif	

#if CHANNEL_A_POLARITY == NON_INVERTING
	//setting channel A direction to output
	setbit(DDRD,CHANNEL_A_PIN);
	//Setting channel A to non-inverting mode
	clearbit(TCCR1A, TCCR1A_COM1A0);
	setbit(TCCR1A, TCCR1A_COM1A1);

#elif CHANNEL_A_POLARITY == INVERTING
	//setting channel A direction to output
	setbit(DDRD,CHANNEL_A_PIN);
	//Setting channel A to inverting mode
	setbit(TCCR1A, TCCR1A_COM1A0);
	setbit(TCCR1A, TCCR1A_COM1A1);

#elif CHANNEL_A_POLARITY == CHANNEL_DISABLE
	//Disabling PWM in channel A
	clearbit(TCCR1A, TCCR1A_COM1A0);
	clearbit(TCCR1A, TCCR1A_COM1A1);	
#endif

#if CHANNEL_B_POLARITY == NON_INVERTING
	//setting channel B direction to output
	setbit(DDRD,CHANNEL_B_PIN);
	//Setting channel A to non-inverting mode
	clearbit(TCCR1A, TCCR1A_COM1B0);
	setbit(TCCR1A, TCCR1A_COM1B1);

#elif CHANNEL_B_POLARITY == INVERTING
	//setting channel B direction to output
	setbit(DDRD,CHANNEL_B_PIN);
	//Setting channel A to inverting mode
	setbit(TCCR1A, TCCR1A_COM1B0);
	setbit(TCCR1A, TCCR1A_COM1B1);

#elif CHANNEL_B_POLARITY == CHANNEL_DISABLE
	//Disabling PWM in channel A
	clearbit(TCCR1A, TCCR1A_COM1B0);
	clearbit(TCCR1A, TCCR1A_COM1B1);
#endif
}


void PWM_Generate_CHANNELA(uint8 Copy_u8DutyCycle,uint32 Copy_u32freq){
/***Generating Fast PWM wave***/
#if PWM_MODULATION_MODE == FAST_PWM_MODE
	//setting prescaler based on the needed frequency
	uint16 prescaler = 1;
	if(((float)F_CPU/Copy_u32freq) < MAX_TOP) prescaler = 1;
	else if(((float)F_CPU/(Copy_u32freq*8)) < MAX_TOP) prescaler = 8;
	else if(((float)F_CPU/(Copy_u32freq*64)) < MAX_TOP) prescaler = 64;
	else if(((float)F_CPU/(Copy_u32freq*256)) < MAX_TOP) prescaler = 256;
	else if(((float)F_CPU/(Copy_u32freq*1024)) < MAX_TOP) prescaler = 1024;

	//calculating TOP value to determine the frequency
	uint16 TOP =  ((float)F_CPU/(Copy_u32freq*prescaler));
	
	//Generating Fast PWM in non-inverting polarity	
#if CHANNEL_A_POLARITY == NON_INVERTING		
	//calculating OCR value to determine the duty cycle
	uint16 OCR_value;
	if(Copy_u8DutyCycle == 0) OCR_value = 0;
	else OCR_value = (((float)Copy_u8DutyCycle*(TOP+1))/255) - 1;	
	
	//setting the registers and starting wave generation
	ICR1 = TOP;
	OCR1A = OCR_value;
	PWM_Start(prescaler);	
#endif
	
	//Generating Fast PWM in inverting polarity	
#if CHANNEL_A_POLARITY == INVERTING
	//calculating OCR value to determine the duty cycle
	uint16 OCR_value;
	if(Copy_u8DutyCycle == 255) OCR_value = 0;
	else OCR_value = TOP - (((float)Copy_u8DutyCycle*(TOP+1))/255);
	
	//setting the registers and starting wave generation
	ICR1 = TOP;
	OCR1A = OCR_value;
	PWM_Start(prescaler);	
#endif
#endif

/***Generating PWM wave with phase correction***/
#if PWM_MODULATION_MODE == PHASE_CORRECT_MODE
	//setting prescaler based on the needed frequency
	uint16 prescaler = 1;
	if(((float)F_CPU/(Copy_u32freq*2)) < (MAX_TOP-1)) prescaler = 1;
	else if(((float)F_CPU/(Copy_u32freq*2*8)) < (MAX_TOP-1)) prescaler = 8;
	else if(((float)F_CPU/(Copy_u32freq*2*64)) < (MAX_TOP-1)) prescaler = 64;
	else if(((float)F_CPU/(Copy_u32freq*2*256)) < (MAX_TOP-1)) prescaler = 256;
	else if(((float)F_CPU/(Copy_u32freq*2*1024)) < (MAX_TOP-1)) prescaler = 1024;
	
	//calculating TOP value to determine the frequency
	uint16 TOP = ((float)F_CPU/(Copy_u32freq*2*prescaler));
	
	//Generating PWM with phase correct in non-inverting polarity	
#if CHANNEL_A_POLARITY == NON_INVERTING
	//calculating OCR value to determine the duty cycle
	uint16 OCR_value = ((float)Copy_u8DutyCycle*TOP)/255;
	
	//setting the registers and starting wave generation
	ICR1 = TOP;
	OCR1A = OCR_value;
	PWM_Start(prescaler);
#endif
	
	//Generating Fast PWM in inverting polarity	
#if CHANNEL_A_POLARITY == INVERTING
	//calculating OCR value to determine the duty cycle
	uint16 OCR_value = TOP - (((float)Copy_u8DutyCycle*TOP)/255);
	
	//setting the registers and starting wave generation
	ICR1 = TOP;
	OCR1A = OCR_value;
	PWM_Start(prescaler);
#endif
#endif	
}


void PWM_Generate_CHANNELB(uint8 Copy_u8DutyCycle,uint32 Copy_u32freq){
	/***Generating Fast PWM wave***/
	#if PWM_MODULATION_MODE == FAST_PWM_MODE
	//setting prescaler based on the needed frequency
	uint16 prescaler = 1;
	if(((float)F_CPU/Copy_u32freq) < MAX_TOP) prescaler = 1;
	else if(((float)F_CPU/(Copy_u32freq*8)) < MAX_TOP) prescaler = 8;
	else if(((float)F_CPU/(Copy_u32freq*64)) < MAX_TOP) prescaler = 64;
	else if(((float)F_CPU/(Copy_u32freq*256)) < MAX_TOP) prescaler = 256;
	else if(((float)F_CPU/(Copy_u32freq*1024)) < MAX_TOP) prescaler = 1024;

	//calculating TOP value to determine the frequency
	uint16 TOP =  ((float)F_CPU/(Copy_u32freq*prescaler));
	
	//Generating Fast PWM in non-inverting polarity
	#if CHANNEL_B_POLARITY == NON_INVERTING
	//calculating OCR value to determine the duty cycle
	uint16 OCR_value;
	if(Copy_u8DutyCycle == 0) OCR_value = 0;
	else OCR_value = (((float)Copy_u8DutyCycle*(TOP+1))/255) - 1;
	
	//setting the registers and starting wave generation
	ICR1 = TOP;
	OCR1B = OCR_value;
	PWM_Start(prescaler);
	#endif
	
	//Generating Fast PWM in inverting polarity
	#if CHANNEL_B_POLARITY == INVERTING
	//calculating OCR value to determine the duty cycle
	uint16 OCR_value;
	if(Copy_u8DutyCycle == 255) OCR_value = 0;
	else OCR_value = TOP - (((float)Copy_u8DutyCycle*(TOP+1))/255);
	
	//setting the registers and starting wave generation
	ICR1 = TOP;
	OCR1B = OCR_value;
	PWM_Start(prescaler);
	#endif
	#endif

	/***Generating PWM wave with phase correction***/
	#if PWM_MODULATION_MODE == PHASE_CORRECT_MODE
	//setting prescaler based on the needed frequency
	uint16 prescaler = 1;
	if(((float)F_CPU/(Copy_u32freq*2)) < (MAX_TOP-1)) prescaler = 1;
	else if(((float)F_CPU/(Copy_u32freq*2*8)) < (MAX_TOP-1)) prescaler = 8;
	else if(((float)F_CPU/(Copy_u32freq*2*64)) < (MAX_TOP-1)) prescaler = 64;
	else if(((float)F_CPU/(Copy_u32freq*2*256)) < (MAX_TOP-1)) prescaler = 256;
	else if(((float)F_CPU/(Copy_u32freq*2*1024)) < (MAX_TOP-1)) prescaler = 1024;
	
	//calculating TOP value to determine the frequency
	uint16 TOP = (F_CPU/(Copy_u32freq*2*prescaler));
	
	
	//Generating PWM with phase correct in non-inverting polarity
	#if CHANNEL_B_POLARITY == NON_INVERTING
	//calculating OCR value to determine the duty cycle
	uint16 OCR_value = ((float)Copy_u8DutyCycle*TOP)/255;
	
	//setting the registers and starting wave generation
	ICR1 = TOP;
	OCR1B = OCR_value;
	PWM_Start(prescaler);
	#endif
	
	//Generating Fast PWM in inverting polarity
	#if CHANNEL_B_POLARITY == INVERTING
	//calculating OCR value to determine the duty cycle
	uint16 OCR_value = TOP - (((float)Copy_u8DutyCycle*TOP)/255);
	
	//setting the registers and starting wave generation
	ICR1 = TOP;
	OCR1B = OCR_value;
	PWM_Start(prescaler);
	#endif
	#endif
}