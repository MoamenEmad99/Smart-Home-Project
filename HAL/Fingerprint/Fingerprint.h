/*
 * Fingerprint.h
 *
 * Created: 3/12/2023 12:54:15 AM
 *  Author: dell
 */ 


#ifndef FINGERPRINT_H_
#define FINGERPRINT_H_

#include "../../LIB/Datatypes.h"


/************************************************************************/
/*						Fingerprint Configurations                      */
/************************************************************************/	
#define FP_BAUDRATE			(57600)			//Baud rate
#define FP_INT				FP_DIS			//interrupt state	
#define LED_CTRL			LED_ON			//LED control mode
#define LED_SPD				255				//LED speed
#define LED_COLOR			LED_BLUE		//LED color
#define LED_TIMES			255				//LED number of times


/*--------LED control modes--------*/
#define LED_BREATHING		(0x01)
#define LED_FLASHING		(0x02)
#define LED_ON				(0x03)
#define LED_OFF				(0x04)
#define LED_GRAD_ON			(0x05)
#define LED_GRAD_OFF		(0x06)

/*-----------LED colors-----------*/
#define LED_RED				(0x01)
#define LED_BLUE			(0x02)
#define LED_PURPLE			(0x03)

/*---------Interrupt modes---------*/
#define FP_DIS				(0)
#define FP_EN				(1)

/*----------Buffer states----------*/
#define FP_WAIT_DATA		(0)
#define FP_DATA_READY		(1)

/*----------return states----------*/
#define PASS				(0)				//successful command
#define ERROR				(1)				//unsuccessful command
#define WRONG_FINGER		(0xFF)			//finger doesn't match any saved template
#define NO_FINGER			(0xFE)			//sensor couldn't detect any finger
#define FINGER_DETECTED		(0xFD)			//sensor detected a finger


/*----------Packet arrays sizes----------*/
#define SIZE_OF_PASS				(16)
#define SIZE_OF_DETECT				(12)
#define SIZE_OF_IMG_TO_CH			(13)
#define SIZE_OF_CREATE_MODEL		(12)
#define SIZE_OF_UPLOAD_MODEL		(13)
#define SIZE_OF_STORE_MODEL			(15)
#define SIZE_OF_SEARCH				(17)
#define SIZE_OF_DELETE				(16)
#define SIZE_OF_AURA_LED			(16)


#define RED_LED		PORT_B, PIN7
#define YEL_LED		PORT_A, PIN6
#define BLU_LED		PORT_A, PIN5
#define GRN_LED		PORT_A, PIN4


/*---------------Fingerprint APIs---------------*/
void UART_ISR(uint16 RXC_data);						//ISR for UART RXC
void flush_buffer(void);							//clears data buffer
uint8 FP_sendCommand(uint8 *pack, uint16 len);		//sends command to fingerprint sensor
void fingerprint_init(uint8 *FP_flag);				//initialize fingerprint
uint8 FP_enrollFinger(uint16 finger_ID);			//add new fingerprint of a certain index to the sensor library
uint16 FP_readFinger(void);							//reads finger and returns the id of the matched template in the sensor library
void FP_deleteFinger(uint16 finger_ID);				//deletes a fingerprint of a certain id from the sensor library
void FP_ISR(void);									//wakeup ISR.. applies when a the sensor detects a finger


void fingerprint_test_init(void);
void fingerprint_test_enroll(uint8 F);
void fingerprint_test_check(uint8 F);

#endif /* FINGERPRINT_H_ */