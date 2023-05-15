/*
 * ultrasonic.h
 *
 * Created: 18/03/2023 03:29:18 ص
 *  Author: aslam
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../../LIB/Datatypes.h"


#define F_CPU              16000000UL

#define                triger_ultra0             PIN5
#define                Echo_ultra0               PIN2
#define                triger_ultra1             PIN4
#define                Echo_ultra1               PIN3

void Ultrasonic_INIT();

uint32 Distance_0_cm();

uint32 Distance_1_cm();
#endif /* ULTRASONIC_H_ */