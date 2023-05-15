/*
 * FAN.h
 *
 * Created: 3/17/2023 2:27:23 PM
 *  Author: dell
 */ 


#ifndef FAN_H_
#define FAN_H_

#include "../../MCAL/DIO/DIO_Interface.h"

//Motor A direction pins
#define EN 					PORT_A, PIN2



//Motor State
#define ON_STATE 			(0)
#define OFF_STATE	 		(1)

//FAN APIs
void FAN_init(); //initialize motor A
void FAN_Rotate(uint8 State); //start motor A motion



#endif /* FAN_H_ */