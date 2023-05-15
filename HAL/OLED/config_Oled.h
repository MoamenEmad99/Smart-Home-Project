/*
 * config_Oled.h
 *
 * Created: 3/14/2023 11:00:31 AM
 *  Author: EslamRamadanBorayekT
 */ 


#ifndef CONFIG_OLED_H_
#define CONFIG_OLED_H_


void init_Oled();

void Command(uint8);
void write_data(uint8);

void clear_Oled();

void write_char(uint8);
void Write_string(uint8 *ptr  );

void go_to_xy(uint8 , uint8);
void go_to_next_line();



#endif /* CONFIG_OLED_H_ */