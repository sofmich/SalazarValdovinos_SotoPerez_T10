/*
 * delay.c
 *	This is a delay function for common implementations. 
 *  Created on: Feb 16, 2020
 *      Author: Momo
 */
#include <stdint.h>

void delay(uint32_t delay)
{
	volatile uint32_t j;
	for(j = delay; j>0; j--)
	{
	}
}
