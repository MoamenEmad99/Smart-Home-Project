/*
 * Smart_Home.c
 *
 * Created: 3/15/2023 12:28:55 PM
 * Author : dell
 */ 

#include "APP/Smart_Home/Smart_Home.h"


int main(void)
{
	smartHome_init();

	while (1)
	{
		smartHome_start();
	}
}

