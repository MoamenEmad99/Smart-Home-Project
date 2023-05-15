/*
 * Fingerprint.c
 *
 * Created: 3/12/2023 12:54:29 AM
 * Author: Team 1
 * 
 *  11:15
 */ 

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/UART/UART_Interface.h"
#include "../../MCAL/TIMER2/Timer2_Interface.h"
#include "../../MCAL/EXTI/External_INT_Interface.h"
#include "Fingerprint.h"

/*************************************************************************************************************/
/*			                   		  Fingerprint Global Variables                                           */
/*************************************************************************************************************/
uint8 *FP_state = NULL;						//pointer to fingerprint flag (used with wakeup interrupt)
uint8 FP_buffer_state = FP_WAIT_DATA;		//state of the data buffer
uint8 FP_buffer[30];						//buffer to store the packet received from the sensor
uint8 buffer_id = 0;						//index of the nest byte to be added to the buffer
uint8 package_content[20];					//data content extracted from the received packet in the buffer
uint16 package_content_len;					//number of bytes in the package content buffer


/***************************************************************************************************************************/
/*                                               Fingerprint Command Packets                                               */
/***************************************************************************************************************************/

//verify password command
const uint8 passPack[]={0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B};

//get image command
const uint8 f_detect[]={0xEF, 0x1, 0xFF, 0xFF, 0xFF, 0xFF, 0x1, 0x0, 0x3, 0x1, 0x0, 0x5};

//converts image to character file and stores it in buffer 1
const uint8 f_img2ch1[]={0xEF, 0x1, 0xFF, 0xFF, 0xFF, 0xFF, 0x1, 0x0, 0x4, 0x2, 0x1, 0x0, 0x8};

//converts image to character file and stores it in buffer 2
const uint8 f_img2ch2[]={0xEF, 0x1, 0xFF, 0xFF, 0xFF, 0xFF, 0x1, 0x0, 0x4, 0x2, 0x2, 0x0, 0x9};

//combines character files in buffer 1 and buffer 2 into a template and stores it in both buffer 1 and bufer 2
const uint8 f_createModel[]={0xEF, 0x1, 0xFF, 0xFF, 0xFF, 0xFF, 0x1, 0x0, 0x3, 0x5, 0x0, 0x9};

//sends the template to the microcontroller	
const uint8 f_uploadModel[]={0xEF, 0x1, 0xFF, 0xFF, 0xFF, 0xFF, 0x1, 0x0, 0x4, 0x8, 0x1, 0x0, 0x0E};

//stores the template in the sensor internal flash
uint8 f_storeModel[]={0xEF, 0x1, 0xFF, 0xFF, 0xFF, 0xFF, 0x1, 0x0, 0x6, 0x6, 0x1, 0x0, 0x1, 0x0, 0xF};

//searches the library to find the template that matches with the character file stored in buffer 1
const uint8 f_search[]={0xEF, 0x1, 0xFF, 0xFF, 0xFF, 0xFF, 0x1, 0x0, 0x8, 0x4, 0x1, 0x0, 0x1, 0x0, 0x7, 0x0, 0x16};

//deletes template from the library
uint8 f_deleteModel[]={0xEF,0x1,0xFF,0xFF,0xFF,0xFF,0x1,0x0,0x7,0xC,0x0,0x0,0x0,0x1,0x0,0x15};

//sets the configrations of the aura LED
uint8 f_auraLED[]={0xEF, 0x1, 0xFF, 0xFF, 0xFF, 0xFF, 0x1, 0x0, 0x7, 0x35, LED_CTRL, LED_SPD, LED_COLOR, LED_TIMES, 0x0, 0x3D};



/**************************************************************************************************/
/*                                        Fingerprint APIs                                        */
/**************************************************************************************************/

/*
* fingerprint initialization function that does the following:
* assigns the address of the fingerprint flag from the APP layer to the fingerprint state pointer
* initialize TIMER0 (delay)
* initialize UART + sets UART callback function
* initialize external interrupt (for wakeup pin) if enabled
* initialize fingerprint sensor by sending the password and connecting to it
* initialize the aura LED
*/	
void fingerprint_init(uint8 *FP_flag){
	FP_state = FP_flag;
	*FP_state = NO_FINGER;
	
	TIMER2_SetConfig();
	
	UART_Set_RXC_callback(UART_ISR);
	UART_init(FP_BAUDRATE);	
	
	if(FP_INT == FP_EN){
		register_EX2(FP_ISR);
		EXT_INT_Init();
		EXT_INT_SET_CONFIG();
	}
	
	//update aura LED command check sum bytes
	uint16 LED_sum = 0x3D + LED_CTRL + LED_COLOR + LED_SPD + LED_TIMES;	
	f_auraLED[14]= (LED_sum>>8) & 0xff;
	f_auraLED[15]= LED_sum & 0xff;
	
	//initialize fingerprint sensor by sending the password
	while(FP_sendCommand(passPack, SIZE_OF_PASS) == ERROR);
	
	//initialize the aura LED
	while(FP_sendCommand(f_auraLED, SIZE_OF_AURA_LED) == ERROR);
}


/*
* UART RXC ISR:
* when a character is received from the sensor, it will be added to the buffer
* and the buffer state will be updated to data ready
*/
void UART_ISR(uint16 RXC_data){
	FP_buffer[buffer_id] = RXC_data;
	buffer_id++;
	
	if(buffer_id>0)
		FP_buffer_state = FP_DATA_READY;
}


/*
* clears the buffer
*/
void flush_buffer(void){
	for(uint8 i=0; i<30; i++)
		FP_buffer[i] = 0;
	buffer_id = 0;
}


/*
* this function is a generic function to send any command to the sensor by passing the command array and the length of that array as arguments:
* clear buffer contents
* transmit the command array to the sensor
* once the buffer state flag is set by the UART ISR, the received packet will be checked
* extract the data from the buffer to the packet content array
* check the received confirmation code and return the result
*/
uint8 FP_sendCommand(uint8 *pack, uint16 len){
	uint8 result = ERROR;

	flush_buffer();

	TIMER2_DelayMilliSeconds_with_Blocking(100);

	for(uint8 i=0; i<len; i++){
		UART_Transmit(pack[i]);
	}

	TIMER2_DelayMilliSeconds_with_Blocking(1000);

	if(FP_buffer_state == FP_DATA_READY){
		if((FP_buffer[0] == 0xEF) && (FP_buffer[1] == 0x01)){
			// check for ack byte
			if(FP_buffer[6] == 0x07){						
				//check for successful operation	
				if(FP_buffer[9] == 0){		
					//read the data frame length
					package_content_len = FP_buffer[7];
					package_content_len<<=8;
					package_content_len |= FP_buffer[8];
					
					//clear packet content buffer
					for(uint8 i=0; i<package_content_len; i++)
						package_content[i]=0;

					//copy the data frame to the packet content buffer
					for(uint8 i=0; i<package_content_len-3; i++)
						package_content[i] = FP_buffer[10+i];   

					result=PASS;
				}

				
				else
					result=ERROR;
			}

		}

		FP_buffer_state = FP_WAIT_DATA;
	}

	return result;
}


/*
* this function is used to add new finger to the sensor library
* read finger image
* convert finger image to character file and store it in buffer 1
* read finger image
* convert finger image to character file and store it in buffer 2
* combine character files in buffer1 and buffer 2 and generate a template
* store the template in the desired id in the memory
*/
uint8 FP_enrollFinger(uint16 finger_ID)
{
	//for(int i=0;i<3;i++)
	//{
		if(FP_sendCommand(f_detect, SIZE_OF_DETECT) == PASS){
		
			if(FP_sendCommand(f_img2ch1, SIZE_OF_IMG_TO_CH) == PASS){
				
				if(FP_sendCommand(f_detect, SIZE_OF_DETECT) == PASS){
				
					if(FP_sendCommand(f_img2ch2, SIZE_OF_IMG_TO_CH) == PASS){
				
						if(FP_sendCommand(f_createModel, SIZE_OF_CREATE_MODEL) == PASS){
							//update the ID bytes
							f_storeModel[11]= (finger_ID>>8) & 0xff;
							f_storeModel[12]= finger_ID & 0xff;
							
							//update check sum bytes
							uint16 store_sum = 14 + finger_ID;
							f_storeModel[13]= (store_sum>>8) & 0xff;
							f_storeModel[14]= store_sum & 0xff;
						
							
							if(FP_sendCommand(f_storeModel, SIZE_OF_STORE_MODEL) == PASS)
							{
								return PASS;
							}
						}
					}
				}
			}
		}
	//	if(i==2)
	//		return NO_FINGER;
	//		
	//}
	
	return ERROR;
}


/*
* this function reads finger and returns the id of the matched template in the sensor library:
* read finger image
* convert finger image to character file and store it in buffer 1
* searches the library to find the template that matches with the character file stored in buffer 1
* return the matched template id
*/
uint16 FP_readFinger(void)
{
	if(FP_sendCommand(f_detect, SIZE_OF_DETECT) == PASS){
		
		if(FP_sendCommand(f_img2ch1, SIZE_OF_IMG_TO_CH) == PASS){
						
			if (FP_sendCommand(f_search, SIZE_OF_SEARCH) == PASS){
				//extract the scanned ID from the data buffer
				uint16 scannedID = package_content[0];
				scannedID<<8;
				scannedID += package_content[1];
				
				//extract the ID score from the data buffer
				uint8 ID_score = package_content[2];
				ID_score<<8;
				ID_score += package_content[3];
										
				return scannedID;
			}
				
			else{
				return WRONG_FINGER;
				}				
		}

	}
return NO_FINGER;
}


/*
* this function deletes the template stored in a certain id
*/
void FP_deleteFinger(uint16 finger_ID){
	// update the ID bytes
	f_deleteModel[10]= (finger_ID>>8) & 0xff;
	f_deleteModel[11]= finger_ID & 0xff;
	
	//update the check sum byes
	uint8 delete_sum = 0x15 + finger_ID;
	f_deleteModel[14]= (delete_sum>>8) & 0xff;
	f_deleteModel[15]= delete_sum & 0xff;
	
	//wait for delete command
	while(FP_sendCommand(f_deleteModel, SIZE_OF_DELETE) != PASS);	
}


/*
* the wakeup ISR.. applies when a the sensor detects a finger
* sets the FP flag to finger detected
*/
void FP_ISR(void){
	*FP_state = FINGER_DETECTED;
}


void fingerprint_test_init(void){
	DIO_vSetPinDirection(RED_LED, OUT);
	DIO_vSetPinDirection(YEL_LED, OUT);
	DIO_vSetPinDirection(BLU_LED, OUT);
	DIO_vSetPinDirection(GRN_LED, OUT);
	
	DIO_vWritePin(RED_LED, LOW);
	DIO_vWritePin(YEL_LED, LOW);
	DIO_vWritePin(BLU_LED, LOW);
	DIO_vWritePin(GRN_LED, LOW);
	
	
	fingerprint_init(NULL);
	DIO_vWritePin(YEL_LED, HIGH);
}

void fingerprint_test_enroll(uint8 F){
	while (FP_enrollFinger(F) != PASS){
		DIO_vWritePin(RED_LED, HIGH);
	}
	
	DIO_vWritePin(RED_LED, LOW);
	DIO_vWritePin(BLU_LED, HIGH);
	
	TIMER0_DelayMilliSeconds_with_Blocking(1000);
}

void fingerprint_test_check(uint8 F){
	uint8 finger = FP_readFinger();
	while (FP_readFinger() == F){
		DIO_vWritePin(RED_LED, HIGH);
	}
	
	DIO_vWritePin(RED_LED, LOW);
	DIO_vWritePin(GRN_LED, HIGH);
	
	TIMER0_DelayMilliSeconds_with_Blocking(1000);
}