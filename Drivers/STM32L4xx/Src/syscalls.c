/*
 * syscalls.c
 *
 *  Created on: 12 Jan 2023
 *      Author: roy.ratcliffe
 */

#include "stm32l4xx.h"

int __io_putchar(int ch) {
	(void)ITM_SendChar(ch);
	return 0;
}
