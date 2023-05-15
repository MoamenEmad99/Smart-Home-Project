/*
 * Servo.h
 *
 *  Created on: Mar 12, 2023
 *      Author: Abdelrhman
 */

#ifndef HAL_SERVO_H_
#define HAL_SERVO_H_

#include "../../LIB/Datatypes.h"

#define ConstantFreqForServo 		(50)

void ServoMotorInit(void);
void ServoMotorRotate(uint8 Degree);

#endif /* HAL_SERVO_H_ */
