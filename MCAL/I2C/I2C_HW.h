/*
 * I2C_HW.h
 *
 *  Created on: Mar 8, 2023
 *      Author: abdelrahman
 */

#ifndef DIO_MCAL_I2C_I2C_HW_H_
#define DIO_MCAL_I2C_I2C_HW_H_




#define                        IC_ACCESS              ((volatile IC_register *)(0x20)) 
#define                        TWEA_bit                 6
#define                        TWEN_bit                 2
#define                        TWINT_bit                7
#define                        TWSTA_bit                5
#define                        TW_status_mask           0xF8
#define                        TWSTO_bit                4


typedef struct IC {

	uint8   TWBR_R;
	uint8    TWSR_R;
	uint8    TWAR_R;
	uint8    TWDR_R;
	uint8   arr[50];
	uint8     TWCR_R;
}IC_register;



#endif /* DIO_MCAL_I2C_I2C_HW_H_ */
