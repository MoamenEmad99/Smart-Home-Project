/*
 * PWM_Reg.h
 *
 * Created: 2/25/2023 8:32:18 PM
 *  Author: dell
 */ 


#ifndef PWM_REG_H_
#define PWM_REG_H_

#define TCCR1A (*(volatile uint8*)(0x4F))
#define TCCR1B (*(volatile uint8*)(0x4E))

#define TCNT1 (*(volatile uint16*)(0x4C))

#define OCR1A (*(volatile uint16*)(0x4A))

#define OCR1B (*(volatile uint16*)(0x48))

#define ICR1 (*(volatile uint16*)(0x46))

#define TIMSK (*(volatile uint8*)(0x59))
#define TIFR (*(volatile uint8*)(0x58))

#define DDRD (*(volatile uint8*)(0x31))

#define TCCR1A_WGM10 0
#define TCCR1A_WGM11 1
#define TCCR1A_FOC1B 2
#define TCCR1A_FOC1A 3
#define TCCR1A_COM1B0 4
#define TCCR1A_COM1B1 5
#define TCCR1A_COM1A0 6
#define TCCR1A_COM1A1 7

#define TCCR1B_CS10 0
#define TCCR1B_CS11 1
#define TCCR1B_CS12 2
#define TCCR1B_WGM12 3
#define TCCR1B_WGM13 4
#define TCCR1B_ICES1 6
#define TCCR1B_ICNC1 7

#define TIMSK_TOIE1 2
#define TIMSK_OCIE1B 3
#define TIMSK_OCIE1A 4
#define TCCR1B_TICIE1 5

#define TIFR_TOV1 2
#define TIFR_OCF1B 3
#define TIFR_OCF1A 4
#define TIFR_ICF1 5

#endif /* PWM_REG_H_ */