/*
 * SPI_Interface.h
 *
 * Created: 3/4/2023 12:16:51 PM
 *  Author: dell
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "../../LIB/Datatypes.h"

/*-------SPI Configs-------*/
#define SPI_MODE		MASTER
#define SPI_INT			SP_DIS
#define DATA_ORDER		MSB_FIRST
#define PRESCALER		128


#define SLAVE	0
#define MASTER	1


#define SCK		7
#define MISO	6
#define MOSI	5
#define SS		4


#define SP_DIS	0
#define SP_EN	1


#define MSB_FIRST 0
#define LSB_FIRST 1



//pointer to function typedef (for isr callback)
typedef void (*SPI_callback_t) (uint8 SPI_data);

//UART SPI interrupt request
#define SPI_INT_vector __vector_12

//ISR macro
#define ISR(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used)); \
void INT_VECT(void)


void SPI_init(void);
uint8 SPI_Transeive(uint8 data);
void SPI_set_callback(SPI_callback_t SPI_callback);


#endif /* SPI_INTERFACE_H_ */