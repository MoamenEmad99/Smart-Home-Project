/*
 * RFID_Interface.h
 *
 * Created: 3/15/2023 3:23:18 PM
 *  Author: dell
 */ 


#ifndef RFID_INTERFACE_H_
#define RFID_INTERFACE_H_

#include "../../LIB/Datatypes.h"


#define RFID_SS					PORT_B, PIN3


// chip commands
#define CMD_Idle				(0x00)
#define CMD_Mem					(0x01)
#define CMD_GenerateRandomID	(0x02)
#define CMD_CalcCRC				(0x03)
#define CMD_Transmit			(0x04)
#define CMD_NoCmdChange			(0x07)
#define CMD_Receive				(0x08)
#define CMD_Transceive			(0x0C)
#define CMD_MFAuthent			(0x0E)
#define CMD_SoftReset			(0x0F)



#define CARD_FOUND		1
#define CARD_NOT_FOUND	2
#define ERROR			3


uint8 RFID_readReg(uint8 reg);
void RFID_writeReg(uint8 reg, uint8 value);
void RFID_clearBitMask(uint8 reg, uint8 mask);
void RFID_setBitMask(uint8 reg, uint8 mask);
void RFID_reset(void);
uint8 RFID_getFirmwareVersion(void);
uint8 RFID_communicate(uint8 command,
uint8 *sendData,
uint8 sendLen,
uint8 *backData,
uint8 *backLen,
uint8 *validBits);
void RFID_init(void);
uint8 RFID_detectCard(void);
uint8 RFID_getCardId(uint8 *uid);

#endif /* RFID_INTERFACE_H_ */