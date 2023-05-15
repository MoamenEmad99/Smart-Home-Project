/*
 * Timer0_Reg.h
 *
 * Created: 2/24/2023 1:35:53 PM
 *  Author: dell
 */ 


#ifndef TIMER2_REG_H_
#define TIMER2_REG_H_

//TIMER2 Registers
#define TCCR2 (*(volatile uint8*)(0x45))
#define TCNT2 (*(volatile uint8*)(0x44))
#define OCR2  (*(volatile uint8*)(0x43))
#define TIMSK (*(volatile uint8*)(0x59))
#define TIFR  (*(volatile uint8*)(0x58))

//TCCR2 register bits
#define TCCR2_CS20 0
#define TCCR2_CS21 1
#define TCCR2_CS22 2
#define TCCR2_WGM21 3
#define TCCR2_COM20 4
#define TCCR2_COM21 5
#define TCCR2_WGM20 6
#define TCCR2_FOC2 7

//TIMSK register bits
#define TIMSK_TOIE2 6
#define TIMSK_OCIE2 7

//TIFR register bits
#define TIFR_TOV2 6
#define TIFR_OCF2 7

#endif /* TIMER0_REG_H_ */
