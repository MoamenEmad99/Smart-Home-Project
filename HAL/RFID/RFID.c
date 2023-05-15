/*
 * RFID.c
 *
 * Created: 3/15/2023 3:23:27 PM
 *  Author: dell
 */ 

#include "../../MCAL/SPI/SPI_Interface.h"
#include "../../MCAL/TIMER2/Timer2_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "RFID_Reg.h"
#include "RFID_Interface.h"


uint8 RFID_readReg(uint8 reg) {
	uint8 data;
	DIO_vWritePin(RFID_SS, LOW);
	SPI_Transeive(((reg<<1) & 0x7E) | 0x80);

	data = SPI_Transeive(0x00);
	DIO_vWritePin(RFID_SS, HIGH);
	return data;
}


void RFID_writeReg(uint8 reg, uint8 value) {	
	DIO_vWritePin(RFID_SS, LOW);
	SPI_Transeive((reg<<1)&0x7E);

	SPI_Transeive(value);
	DIO_vWritePin(RFID_SS, HIGH);
}


void RFID_clearBitMask(uint8 reg, uint8 mask) {
	uint8 tmp = RFID_readReg(reg);
	RFID_writeReg(reg, tmp & (~mask));
}


void RFID_setBitMask(uint8 reg, uint8 mask) {
	uint8 tmp = RFID_readReg(reg);
	RFID_writeReg(reg, tmp | mask);
}


void RFID_reset(void) {
	RFID_writeReg(CommandReg, CMD_SoftReset);
	TIMER2_DelayMilliSeconds_with_Blocking(50);
	while (RFID_readReg(CommandReg) & 0x08);
}


uint8 RFID_getFirmwareVersion(void) { //0x92
	uint8 v = RFID_readReg(VersionReg);
	return v;
}


uint8 RFID_communicate(uint8 command,
uint8 *sendData,
uint8 sendLen,
uint8 *backData,
uint8 *backLen,
uint8 *validBits) {
	uint8 waitIRq = 0, n, _validBits = 0;
	
	uint8 bitFraming = (uint8) (validBits ? *validBits : 0);
	
	if (command == CMD_Transceive) {
		waitIRq = 0x30;
	} 
	else if (command == CMD_MFAuthent) {
		waitIRq = 0x10;
	}
	
	RFID_writeReg(CommandReg, CMD_Idle);
	
	RFID_writeReg(ComIrqReg, 0x7F);
	RFID_setBitMask(FIFOLevelReg, 0x80);
	
	for (uint8 i=0; i<sendLen; i++)
	{
		RFID_writeReg(FIFODataReg, sendData[i]);
	}
	
	RFID_writeReg(BitFramingReg, bitFraming);
	RFID_writeReg(CommandReg, command);
	if (command == CMD_Transceive) {
		RFID_setBitMask(BitFramingReg, 0x80);
	}
	
	for (int i = 2000; i > 0;) {
		n = RFID_readReg(ComIrqReg);
		if (n & waitIRq) {
			break;
		}
		if (n & 0x01) {
			return 0;
		}
		if (--i == 0) {
			return 0;
		}
	}
	
	uint8 errorRegValue = RFID_readReg(ErrorReg);
	if (errorRegValue & 0x13) {
		return 0;
	}
	
	if (backData && backLen) {
		n = RFID_readReg(FIFOLevelReg);
						
		if (n > *backLen || n == 0) {
			return 0;
		}
		
		*backLen = n;
		
		for (uint8 i=0; i<n; i++)
		{
			backData[i] = RFID_readReg(FIFODataReg);
		}
		
		_validBits = (uint8) (RFID_readReg(ControlReg) & 0x07);
		if (validBits) {
			*validBits = _validBits;
		}
	}
	
	if (errorRegValue & 0x08) {
		return 0;
	}

	return 1;
}


void RFID_init(void) {
	DIO_vSetPinDirection(RFID_SS, OUT);
	DIO_vWritePin(RFID_SS, HIGH);
	TIMER2_SetConfig();
	SPI_init();
	
	RFID_reset();
		
	RFID_writeReg(TModeReg, 0x80);
	RFID_writeReg(TPrescalerReg, 0x9A);
	RFID_writeReg(TReloadRegH, 0x03);
	RFID_writeReg(TReloadRegL, 0xE8);
	
	RFID_writeReg(TxASKReg, 0x40);
	RFID_writeReg(ModeReg, 0x3D);
	
	uint8 value = RFID_readReg(TxControlReg);
	if ((value & 0x03) != 0x03) {
		RFID_setBitMask(TxControlReg, 0x03);
	}
}


uint8 RFID_detectCard(void) {
	uint8 buffer[2];
	uint8 len = sizeof(buffer);
	uint8 validBits = 7;
	
	RFID_clearBitMask(CollReg, 0x80);
	uint8 command[1] = {0x26};
	if (!RFID_communicate(CMD_Transceive, command, 1, buffer, &len, &validBits)) {
		return 0;
	}
	if (len != 2 || validBits != 0) {
		return 0;
	}
	return 1;
}


uint8 RFID_getCardId(uint8 *id) {
	uint8 buffer[9];
	uint8 backLen = 9;
	
	RFID_clearBitMask(CollReg, 0x80);
	RFID_writeReg(BitFramingReg, 0);
	buffer[0] = 0x93;
	buffer[1] = 0x20;
	
	if (!RFID_communicate(CMD_Transceive, buffer, (uint8) 2, buffer, &backLen, 0)) {
		return 0;
	}
	for (int i = 0; i < 4; i++) {
		id[i] = buffer[i];
	}
	
	return 1;
}