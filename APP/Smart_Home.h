/*
 * Smart_Home.h
 *
 * Created: 3/16/2023 6:45:24 PM
 *  Author: dell
 */ 


#ifndef SMART_HOME_H_
#define SMART_HOME_H_

#include "../LIB/Datatypes.h"


#define SYSTEM_OFF				(0)
#define SYSTEM_ON				(1)
#define SYSTEM_SHUTDOWN			(2)
#define SYSTEM_START			(3)


#define FAN_OFF					(0)
#define FAN_ON					(1)


#define DOOR_LOCKED			(0)
#define DOOR_OPENED			(90)

#define DISTANCE_RANGE		(30)
#define NOT_DETECTED		(0)
#define DETECTED			(1)


#define NO_ONE				(0)
#define MOAMEN				(1)
#define ESLAM				(2)
#define TONY				(3)
#define ABDO				(4)
#define KAREEM				(5)


uint8 checkCardID(uint8 *id, uint8 *stored_id);
void door_system(void);
void fan_system(void);
void login_system(void);
void shutdown_system(void);
void start_system(void);
void button_ISR(void);
void count_people(void);
void light_system(void);
void smartHome_init(void);
void smartHome_start(void);


#endif /* SMART_HOME_H_ */