/*
 * SPI.c
 *
 * Created: 3/4/2023 12:17:06 PM
 *  Author: dell
 */ 

#include "SPI_Interface.h"
#include "SPI_Reg.h"
#include "../../LIB/Calcbit.h"

static SPI_callback_t SPI_callback_ptr = NULL;

void SPI_init(void){
#if SPI_MODE == MASTER
	//set pins directions
	setbit(DDRB,MOSI);
	setbit(DDRB,SCK);
	clearbit(DDRB,MISO);
	setbit(DDRB,SS);
	setbit(PORTB,SS);
	//enable as master
	setbit(SPCR,MSTR);
	
	//set phase and polarity configs
	clearbit(SPCR,CPOL);
	clearbit(SPCR,CPHA);
#endif

#if SPI_MODE == SLAVE
	//set pins directions
	clearbit(DDRB,MOSI);
	clearbit(DDRB,SCK);
	clearbit(DDRB,SS);
	setbit(DDRB,MISO);

	//enable as slave
	clearbit(SPCR,MSTR);

	//set phase and polarity configs
	clearbit(SPCR,CPOL);
	clearbit(SPCR,CPHA);
#endif

	//set interrupt configs
	if(SPI_INT == SP_EN){
		setbit(SREG,GIE);
		setbit(SPCR,SPIE);
	}
	else if(SPI_INT == SP_DIS) clearbit(SPCR,SPIE);
	
	//set data order configs
	if(DATA_ORDER == MSB_FIRST) clearbit(SPCR,DORD);
	else if(DATA_ORDER == LSB_FIRST) setbit(SPCR,DORD);
	
	switch(PRESCALER){
		case 2:
			clearbit(SPCR,SPR0);
			clearbit(SPCR,SPR1);
			setbit(SPSR,SPI2X);
			break;
			
		case 4:
			clearbit(SPCR,SPR0);
			clearbit(SPCR,SPR1);
			clearbit(SPSR,SPI2X);
			break;
			
		case 8:
			setbit(SPCR,SPR0);
			clearbit(SPCR,SPR1);
			setbit(SPSR,SPI2X);
			break;
			
		case 16:
			setbit(SPCR,SPR0);
			clearbit(SPCR,SPR1);
			clearbit(SPSR,SPI2X);
			break;
			
		case 32:
			clearbit(SPCR,SPR0);
			setbit(SPCR,SPR1);
			setbit(SPSR,SPI2X);
			break;
			
		case 64:
			clearbit(SPCR,SPR0);
			setbit(SPCR,SPR1);
			clearbit(SPSR,SPI2X);
			break;	
			
		case 128:
			setbit(SPCR,SPR0);
			setbit(SPCR,SPR1);
			clearbit(SPSR,SPI2X);
			break;					
	}
	
	setbit(SPCR,SPE); //enable SPI

}

uint8 SPI_Transeive(uint8 data){
	SPDR = data;
	while(getbit(SPSR,SPIF)==0);
	return SPDR;
}

void SPI_set_callback(SPI_callback_t SPI_callback){
	SPI_callback_ptr = SPI_callback;
}

ISR(SPI_INT_vector){
	uint8 SPI_data = SPDR;
	SPI_callback_ptr(SPI_data);
}