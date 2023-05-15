/*
 * data_types_i2c.h
 *
 * Created: 3/8/2023 2:15:20 PM
 *  Author: EslamRamadanBorayekT
 */ 


#ifndef DATA_TYPES_I2C_H_
#define DATA_TYPES_I2C_H_

typedef enum {start_failed , ack_recieved , nack_recieved , SLA_W_failed  , repeated_start_failed , data_tr_failed , ack_returned}state_I2C;



#endif /* DATA_TYPES_I2C_H_ */