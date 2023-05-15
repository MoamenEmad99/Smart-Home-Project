/*
 * DIO_Interface.h
 *
 * Created: 2/17/2023 7:32:33 PM
 *  Author: dell
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "DIO_Reg.h"


//portNames
#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'

//pinNames
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


//pin direction
#define IN 0
#define OUT 1
#define IN_PULLUP 2


//pin value
#define LOW 0
#define HIGH 1

//setting the direction of a pin i/o
void DIO_vSetPinDirection(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber, uint8 copy_u8state);

//writes a value to a pin HIGH/LOW
void DIO_vWritePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber, uint8 Copy_u8value);

//toggles value on a pin
void DIO_vTogglePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber);

//setting the direction of a port i/o
void DIO_vSetPortDirection(uint8 Copy_u8PORT, uint8 copy_u8state);

//writes a value to a port HIGH/LOW
void DIO_vWritePort(uint8 Copy_u8PORT, uint8 Copy_u8value);

//returns the value on a pin HIGH/LOW
uint8 DIO_u8GetPinValue(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber);

//returns the value on a port (binary)
uint8 DIO_u8GetPortValue(uint8 Copy_u8PORT);

//toggles all pins on a port
void DIO_vTogglePort(uint8 Copy_u8PORT);

//writes a value to a port (binary)
void DIO_vWritePortValue(uint8 Copy_u8PORT, uint8 Copy_u8value);


#endif /* DIO_INTERFACE_H_ */