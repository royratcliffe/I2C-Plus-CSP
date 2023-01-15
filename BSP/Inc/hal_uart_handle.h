/*
 * hal_uart_handle.h
 *
 *  Created on: 15 Jan 2023
 *      Author: Roy Ratcliffe
 */

#pragma once

#include "stm32l4xx.h"

UART_HandleTypeDef *HAL_UART_Handle_For_Name(const char *name);
const char *HAL_UART_Name_For_Handle(UART_HandleTypeDef *huart);
