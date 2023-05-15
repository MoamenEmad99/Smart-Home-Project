/*
 * DIO_Reg.h
 *
 * Created: 2/17/2023 7:32:14 PM
 *  Author: dell
 */ 


#ifndef DIO_REG_H_
#define DIO_REG_H_

#include "../../LIB/Calcbit.h"
#include "../../LIB/Datatypes.h"

//base address for each port (Pin register of each port is the base address of th struct)
#define PORTA_BASE ((volatile DIO_Regs*)(0x39))
#define PORTB_BASE ((volatile DIO_Regs*)(0x36))
#define PORTC_BASE ((volatile DIO_Regs*)(0x33))
#define PORTD_BASE ((volatile DIO_Regs*)(0x30))

typedef struct
{
	uint8 Pin;
	uint8 DDR;
	uint8 Port;
}DIO_Regs;



#endif /* DIO_REG_H_ */