/*
 * SPI_Reg.h
 *
 * Created: 3/4/2023 12:16:01 PM
 *  Author: dell
 */ 


#ifndef SPI_REG_H_
#define SPI_REG_H_

#include "../../LIB/Datatypes.h"

/* SPI Registers */
#define  SREG	(*(volatile uint8*)(0x5F))
#define  SPDR	(*(volatile uint8*)(0x2F))
#define  SPSR	(*(volatile uint8*)(0x2E))
#define  SPCR	(*(volatile uint8*)(0x2D))
#define  DDRB	(*(volatile uint8*)(0x37))
#define  PORTB	(*(volatile uint8*)(0x38))



//global interrupt enable bit in SREG
#define GIE		7

/* SPSR bits */
#define SPIE	7
#define SPE		6
#define DORD	5
#define MSTR	4
#define CPOL	3
#define CPHA	2
#define SPR1	1
#define SPR0	0

/* SPSR bits */
#define SPIF	7
#define WCOL	6
#define SPI2X	0

#endif /* SPI_REG_H_ */