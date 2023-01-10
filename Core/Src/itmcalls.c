/*
 * itmcalls.c
 *
 *  Created on: Jan 01, 2023
 *      Author: Roy Ratcliffe
 */

#include "stm32l4xx.h"

int __io_putchar(int ch) {
	return ITM_SendChar(ch);
}
