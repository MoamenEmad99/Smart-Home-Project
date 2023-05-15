/*
 * Timer0_Reg.h
 *
 * Created: 2/24/2023 1:35:53 PM
 *  Author: dell
 */ 


#ifndef TIMER0_REG_H_
#define TIMER0_REG_H_

//TIMER0 Registers
#define SREG	(*(volatile uint8*)(0x5F))
#define TCCR0 (*(volatile uint8*)(0x53))
#define TCNT0 (*(volatile uint8*)(0x52))
#define OCR0 (*(volatile uint8*)(0x5C))
#define TIMSK (*(volatile uint8*)(0x59))
#define TIFR (*(volatile uint8*)(0x58))

//global interrupt enable bin
#define GIE			7

//TCCR0 register bits
#define TCCR0_CS00 0
#define TCCR0_CS01 1
#define TCCR0_CS02 2
#define TCCR0_WGM01 3
#define TCCR0_COM00 4
#define TCCR0_COM01 5
#define TCCR0_WGM00 6
#define TCCR0_FOC0 7

//TIMSK register bits
#define TIMSK_TOIE0 0
#define TIMSK_OCIE0 1

//TIFR register bits
#define TIFR_TOV0 0
#define TIFR_OCF0 1

#endif /* TIMER0_REG_H_ */