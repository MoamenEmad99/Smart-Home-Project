
#include "../../MCAL/PWM/PWM_Interface.h"
#include "Servo.h"

void ServoMotorInit(void)
{
	PWM_Init();
}

void ServoMotorRotate(uint8 Degree)
{
	uint8 Duty;
	Duty = 0.16666666 * Degree + 6;
	PWM_Generate_CHANNELA(Duty,ConstantFreqForServo);

}


