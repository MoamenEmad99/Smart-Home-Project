/*
 * I2C_config.h
 *
 *  Created on: Mar 8, 2023
 *      Author: abdelrahman
 */

#ifndef DIO_MCAL_I2C_I2C_CONFIG_H_
#define DIO_MCAL_I2C_I2C_CONFIG_H_

#include "data_types_i2c.h"
#include "../../LIB/Datatypes.h"


static uint8  division_factor = 30;







/*master function*/
void init_I2C(void);

uint8 START_I2C(uint8 slave);   
uint8 repeated_start(uint8 slave);
uint8  write_I2C(uint8 data);
uint8 read_ack();
uint8 read_nack();
void stop_I2C();

/*slave functions*/

void I2C_Slave_Init(uint8 slave_address);
uint8 I2C_Slave_Listen();
int I2C_Slave_Transmit(uint8 data);
char  I2C_Slave_Receive();
void slave_stop();
#endif /* DIO_MCAL_I2C_I2C_CONFIG_H_ */
