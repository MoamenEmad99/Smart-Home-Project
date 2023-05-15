/*
 * Oled.c
 *
 * Created: 3/11/2023 1:31:04 PM
 *  Author: EslamRamadanBorayekT
 */ 

#include "../../LIB/Datatypes.h"
#include "Oled.h"
#include "../../MCAL/I2C/I2C_config.h"
#include "../../LIB/Calcbit.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/TIMER2/Timer2_Interface.h"
#include "config_Oled.h"

uint8 line_number=0 , line_pos=0;


void init_Oled(){
	
TIMER2_SetConfig();			

init_I2C();
   Command(SSD1306_DISPLAY_OFF);
   Command(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
   Command(0x80);
   Command(SSD1306_SET_MULTIPLEX_RATIO);
   Command(0x3F);
   Command(SSD1306_SET_DISPLAY_OFFSET);
   Command(0x0);
   Command(SSD1306_SET_START_LINE | 0x0);
   Command(SSD1306_CHARGE_PUMP);
   Command(0x14);
   Command(SSD1306_MEMORY_ADDR_MODE);
   Command(0x00);
   Command(SSD1306_SET_SEGMENT_REMAP | 0x1);
   Command(SSD1306_COM_SCAN_DIR_DEC);
   Command(SSD1306_SET_COM_PINS);
   Command(0x12);
   Command(SSD1306_SET_CONTRAST_CONTROL);
   Command(0xCF);
   Command(SSD1306_SET_PRECHARGE_PERIOD);
   Command(0xF1);
   Command(SSD1306_SET_VCOM_DESELECT);
   Command(0x40);
   Command(SSD1306_DISPLAY_ALL_ON_RESUME);
   Command(SSD1306_NORMAL_DISPLAY);
   Command(SSD1306_DISPLAY_ON);

clear_Oled();



}


void Command(uint8 cmd){
START_I2C(0x78);	
	
write_I2C(0x80);
write_I2C(cmd);	
 stop_I2C();	
	
TIMER2_DelayMilliSeconds_with_Blocking(5);	
	
}




void clear_Oled(){
  int i;

Command(SSD1306_SET_COLUMN_ADDR);
  Command(0);
  Command(127);

  Command(SSD1306_SET_PAGE_ADDR);
  Command(0);
  Command(7);


  START_I2C(SSD1306_ADDRESS);
  write_I2C(SSD1306_DATA_CONTINUE);

  for (i=0; i<1024; i++)      // Write Zeros to clear the display
  {
	  write_I2C(0x00);
  }

  Command(SSD1306_SET_COLUMN_ADDR);
  Command(0);
  Command(127);

  Command(SSD1306_SET_PAGE_ADDR);
  Command(0);
  Command(7);

	
}


void write_data(uint8 data){
	
START_I2C(SSD1306_ADDRESS);

write_I2C(0x40);
write_I2C(data);
line_pos++;
stop_I2C();

	
	}
	


void write_char(uint8 data){

data = data - 0x20;

for(int i=0 ; i<5 ;i++ ){
write_data(fonts[data ][i] );
}	

line_pos++;
go_to_xy(line_number ,line_pos );
TIMER2_DelayMilliSeconds_with_Blocking(50);
	
}



void go_to_xy(uint8 l_n, uint8 L_P){
	if(l_n <= 0x07  && L_P <= 127){

		Command(SSD1306_SET_COLUMN_ADDR);
		Command(L_P);
		Command(127);

		Command(SSD1306_SET_PAGE_ADDR);
		Command(l_n);
		Command(7);

		line_number = l_n;
		line_pos = L_P;

	}
}

void go_to_next_line(){
	line_number++;
	line_number&=(0x07);
	go_to_xy(line_number , 0);
}


void Write_string(uint8 *ptr   ){
	int i =0 ;
	while(ptr[i]){
	write_char( ptr [i]);	
		i++;		
	}
	TIMER2_DelayMilliSeconds_with_Blocking(50);
}


	