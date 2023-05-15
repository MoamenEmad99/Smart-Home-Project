/*
 * Smart_Home.c
 *
 * Created: 3/16/2023 6:53:59 PM
 *  Author: Team 1
 */ 
/************************************************************************/
/*                        All HAL Layer Includes                        */
/************************************************************************/
#include "../../HAL/Buzzer/Buzzer.h"
#include "../../HAL/Fingerprint/Fingerprint.h"
#include "../../HAL/FAN/FAN.h"
#include "../../HAL/LED/LED.h"
#include "../../HAL/LM35/LM35.h"
#include "../../HAL/OLED/config_Oled.h"
#include "../../HAL/RFID/RFID_Interface.h"
#include "../../HAL/Servo/Servo.h"
#include "../../HAL/Ultrasonic/ultrasonic.h"
#include "../../HAL/Push_Buton/Button.h"
#include "../../HAL/DELAY/DELAY.h"
#include "Smart_Home.h"

/************************************************************************/
/*                         All Global Variables                         */
/************************************************************************/
/*----------------System States & Flags----------------*/
uint8 systemState = SYSTEM_OFF;			//indicates the state of the whole system (starts from off state)
uint8 finger = NO_ONE;					//holds the id of the fingerprint of the logged in member when 
uint8 doorState = DOOR_LOCKED;			//state of the door
uint8 fanState = FAN_OFF;				//state of the fan
uint8 temperature;						//system temperature
uint8 people = 0;						//number of people in the house

/*-------------Other Global Variables-------------*/	
const uint8 card1_id[] = {0x53, 0x95, 0xFE, 0x0A};		//the id of the first RFID card
const uint8 card2_id[] = {0x89, 0x79, 0xC7, 0xC1};		//the id of the second RFID card

uint8 ultrasonic0_flag = 0;								//this flag is set when the first ultrasonic senses a person
uint8 ultrasonic1_flag = 0;								//this flag is set when the swcond ultrasonic senses a person
	

/*
* this function compares between two card ids
* input: 2 arrays of size 4
* output: 1 if matched, 0 if unmatched
*/
uint8 checkCardID(uint8 *id, uint8 *stored_id){
	for(uint8 i=0; i<4; i++)
		if(id[i] != stored_id[i])
			return 0;	
	return 1;
}

/*
* this function opens the door and sets its state flag when the RFID reads the correct card
*/
void door_system(void){
	uint8 card[4];
	if(RFID_detectCard()){														//if card is detected
		if(RFID_getCardId(card)){												//reads the card is and assigns it in the array
			if(checkCardID(card, card1_id) || checkCardID(card, card2_id)){		//if the read id equals card1 id or card2 id
				if(doorState == DOOR_LOCKED){									//open the door if locked
					ServoMotorRotate(DOOR_OPENED);
					doorState = DOOR_OPENED;
				}
				else{															//lock the door if opened
					ServoMotorRotate(DOOR_LOCKED);
					doorState = DOOR_LOCKED;
				}
			}
		}
	}	
}


/*
* this function controls the fan and the alert based on the temperature value and  
*/
void fan_system(void)
{
	temperature = LM35_read();		//reads temperature
	if(temperature >= 35)			//if T>=35, turn fan on, set fan state flag to on state, tur buzzer on
	{
		FAN_Rotate(ON_STATE);
		fanState = FAN_ON;
		Buzzer_on(0);
	}
	else if(temperature >= 30)		//if T>=30, turn fan on, set fan state flag to on state, tur buzzer off
	{
		if(fanState == OFF_STATE){
			FAN_Rotate(ON_STATE);
			fanState = FAN_ON;
			Buzzer_off();
		}

	}
	else if(temperature >= 28)		//if T>=28, turn fan on, set fan state flag to off state, tur buzzer off
	{
		if(fanState == ON_STATE){
			FAN_Rotate(OFF_STATE);
			fanState = FAN_OFF;
			Buzzer_off();
		}
	}
	else
	{									//if T<27, turn fan off, set fan state flag to off state, tur buzzer off
		FAN_Rotate(OFF_STATE);
		fanState = FAN_OFF;
		Buzzer_off();
	}
}


/*
* this function loops on the fingerprint read function and sets the system state flag to system start when the correct finger is detected
* prints the name of the user detected
*/
void login_system(void){
	Write_string("Place Your finger");
	go_to_next_line();
	while(systemState == SYSTEM_OFF){
		finger = FP_readFinger();
		if (finger == MOAMEN){
				Write_string("Welcome...");
				go_to_next_line();
				Write_string("Moamen Emad");
				go_to_next_line();
				systemState = SYSTEM_START;
			
				while(FP_readFinger() == PASS);
		}
			
		else if (finger == ABDO){
			Write_string("Welcome...");
			go_to_next_line();
			Write_string("Abdelrahman Mahmoud");
			go_to_next_line();
			systemState = SYSTEM_START;
			
			while(FP_readFinger() == PASS);
		}
			
		else if (finger == ESLAM){
			Write_string("Welcome...");
			go_to_next_line();
			Write_string("Eslam Ramadan");
			go_to_next_line();
			systemState = SYSTEM_START;
			
			while(FP_readFinger() == PASS);
		}

		else if (finger == TONY){
			Write_string("Welcome...");
			go_to_next_line();
			Write_string("Antonius Asaad");
			go_to_next_line();
			systemState = SYSTEM_START;
			
			while(FP_readFinger() == PASS);
		}

		else if (finger == KAREEM){
			Write_string("Welcome...");
			go_to_next_line();
			Write_string("Kareem Sameh");
			go_to_next_line();
			systemState = SYSTEM_START;
			
			while(FP_readFinger() == PASS);
		}

		else if (finger == WRONG_FINGER){
			Write_string("Wrong Finger!!");
			go_to_next_line();
			
			while(FP_readFinger() == WRONG_FINGER);	
		}
											
	}
}


/*
* this function takes place when the system state flag is shutdown 
* resets all hardware components and flags
* sets system state flag to system off
*/
void shutdown_system(void){
	//clear screen
	clear_Oled();
	go_to_xy(0,0);
	Write_string("Shutting Down..");
	
	//reset all hardware and flags
	ServoMotorRotate(DOOR_LOCKED);
	FAN_Rotate(OFF_STATE);
	people=0;
	LED_off(YEL_LED);
	LED_off(BLU_LED);
	LED_off(GRN_LED);
	finger = NO_ONE;
	systemState = SYSTEM_OFF;
	delayMilliSeconds(2000);
	
	//clear screen
	clear_Oled();
	go_to_xy(0,0);
}


/*
* push button ISR... sets system state flag to system shutdown 
*/
void button_ISR(void){
	if(systemState == SYSTEM_ON)
		systemState = SYSTEM_SHUTDOWN;
}

/*
* this function applies when system state flag is system start
* only takes place once after fingerprint is detected successfully
* clears screen and prints "system started"
*/
void start_system(void){
	clear_Oled();
	go_to_xy(0,0);
	delayMilliSeconds(500);
	Write_string("System Started!!");
	go_to_next_line();
	systemState = SYSTEM_ON;
	
}


/*
* this function prints all system states
*/
void printStates(void){
	// go to second line on the oled
	go_to_xy(1,0);
	
	//print temperature
	uint8 temp_str[13];
	sprintf(temp_str, "Temp = %d C  ", temperature);
	Write_string(temp_str);
	go_to_next_line();
	
	//print door state
	if(doorState == DOOR_OPENED) Write_string("Door: Opened");
	else if(doorState == DOOR_LOCKED) Write_string("Door: Locked");
	go_to_next_line();
	
	//print fan state
	if(fanState == FAN_ON) Write_string("Fan: ON ");	
	else if(fanState == FAN_OFF) Write_string("Fan: OFF");
	go_to_next_line();
	
	//print number of prople
	uint8 count_str[23];
	sprintf(count_str, "Number of people: %d  ", people);
	Write_string(count_str);
	go_to_next_line();
}



void count_people(void){
	if(doorState == DOOR_OPENED){
		uint8 ultrasonic0 = NOT_DETECTED;
		uint8 ultrasonic1 = NOT_DETECTED;
			
		uint8 counter = 0;
		for(uint8 k=0; k<8; k++){
			if(Distance_0_cm() <= DISTANCE_RANGE) counter++;
			delayMilliSeconds(2);
		}
	
		if(counter>=4){
			while(Distance_0_cm() <= DISTANCE_RANGE);
			ultrasonic0 = DETECTED;
		}
		counter = 0;
	
		for(uint8 k=0; k<8; k++){
			if(Distance_1_cm() <= DISTANCE_RANGE) counter++;
			delayMilliSeconds(2);
		}
	
		if(counter>=4){
			while(Distance_1_cm() <= DISTANCE_RANGE);
			ultrasonic1 = DETECTED;
		}
	
		if(ultrasonic0==DETECTED && ultrasonic1==NOT_DETECTED){
			ultrasonic0_flag = 1;
			if(ultrasonic1_flag == 1){
				ultrasonic1_flag = 0;
				ultrasonic0_flag = 0;
				people++;
			}
		}
	
		else if(ultrasonic1==DETECTED && ultrasonic0==NOT_DETECTED){
			ultrasonic1_flag = 1;
			if(ultrasonic0_flag == 1){
				ultrasonic1_flag = 0;
				ultrasonic0_flag = 0;
				if(people>0){
					people--;
				}
			}
		}
	}

}


/*
* turn on number of LEDs based on number of people
*/
void light_system(void){
	if(people < 2){
		LED_on(YEL_LED);
		LED_off(BLU_LED);
		LED_off(GRN_LED);
	}
	else if(people <= 3){
		LED_on(YEL_LED);
		LED_on(BLU_LED);
		LED_off(GRN_LED);
	}
	else {
		LED_on(YEL_LED);
		LED_on(BLU_LED);
		LED_on(GRN_LED);
	}	
}

/*
* initialize all system hardware
*/
void smartHome_init(void){
	//initialize lighting system 
	LED_init(YEL_LED);
	LED_init(BLU_LED);
	LED_init(GRN_LED);
	Ultrasonic_INIT();
	
	//initialize door system
	RFID_init();
	ServoMotorInit();
	
	//initialize fan system
	LM35_init();
	FAN_init();
	Buzzer_init();
	
	//initialize shutdown system
	button_with_INT_init(button_ISR);
	fingerprint_init(NULL);
	
	//initialize oled
	init_Oled();
	delayMilliSeconds(200);
}


void smartHome_start(void){
	if(systemState == SYSTEM_SHUTDOWN){
		shutdown_system();
	}
	
	else if(systemState == SYSTEM_OFF){
		login_system();
	}
	else if(systemState == SYSTEM_START){
		start_system();
	}
	
	else if(systemState == SYSTEM_ON){
		door_system();
		fan_system();
		light_system();
		printStates();
		count_people();
	}
}
