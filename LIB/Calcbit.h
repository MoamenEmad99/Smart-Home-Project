/*
 * LIB.h
 *
 * Created: 2/17/2023 7:34:42 PM
 *  Author: dell
 */ 


#ifndef LIB_H_
#define LIB_H_

#define setbit(reg,bit_no) ((reg) |= (1<<(bit_no)))
#define clearbit(reg,bit_no) ((reg) &= (~(1<<bit_no)))
#define getbit(reg,bit_no) (((reg)>>bit_no) & 1)
#define togglebit(reg,bit_no) ((reg) ^= (1<<(bit_no)))




#endif /* LIB_H_ */