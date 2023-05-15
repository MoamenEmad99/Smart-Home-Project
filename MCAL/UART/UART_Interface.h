/*
 * UART_Interface.h
 *
 * Created: 3/3/2023 12:00:07 PM
 *  Author: dell
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "../../LIB/Datatypes.h"


#define U_DIS 	0
#define U_EN 	1

#define ONE_BIT 	0
#define TWO_BITS 	1

#define SIZE_5 	0
#define SIZE_6 	1
#define SIZE_7 	2
#define SIZE_8 	3
#define SIZE_9 	4


#define EVEN_PARITY 	2
#define ODD_PARITY 		1
#define DIS_PARITY 		0


typedef struct
{
	uint8 Parity_Mode;
	uint8 Stop_Bit;
	uint8 CHAR_SIZE;
	uint8 RX_INT;
}UART_CONFIG;

static UART_CONFIG UARTConfig = {
	DIS_PARITY,
	ONE_BIT,
	SIZE_8,
	U_EN,
	};


//pointer to function typedef (for isr callback)
typedef void (*RXC_callback_t) (uint16 RXC_data);

//UART RX interrupt request
#define UART_RX_INT __vector_13

//ISR macro
#define ISR(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used)); \
void INT_VECT(void)



uint8 is_normalMode(uint32 BaudRate);
void UART_init (uint32 BaudRate);
void UART_Transmit(uint16 data);
uint16 UART_Recieve(void);
void UART_Set_RXC_callback(RXC_callback_t RXC_callback);



#endif /* UART_INTERFACE_H_ */