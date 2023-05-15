/*
 * Buzzer.h
 *
 * Created: 3/12/2023 1:05:39 PM
 *  Author: dell
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/DIO/DIO_Interface.h"


#define  BUZZER_PORT   PORT_C
#define  BUZZER_PIN		PIN6


// initializes buzzer's configurations
void Buzzer_init(void);
// turns buzzer on
void Buzzer_on(uint16 milliseconds);

void Buzzer_alert(uint16 milliseconds);
// turns buzzer off
void Buzzer_off(void);




#endif /* BUZZER_H_ */