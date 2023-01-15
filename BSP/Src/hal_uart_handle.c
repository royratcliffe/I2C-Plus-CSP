/*
 * hal_uart_handle.c
 *
 *  Created on: 15 Jan 2023
 *      Author: Roy Ratcliffe
 */

#include "hal_uart_handle.h"

#include "pairings.h"

static struct pairing *uart_for_name = NULL;

UART_HandleTypeDef *HAL_UART_Handle_For_Name(const char *name) {
  return right_for_left_stricmp_pairing(&uart_for_name, (void *)name);
}

const char *HAL_UART_Name_For_Handle(UART_HandleTypeDef *huart) {
  return left_for_right_pairing(&uart_for_name, huart);
}

extern UART_HandleTypeDef hlpuart1 __attribute__((weak));
extern UART_HandleTypeDef husart1 __attribute__((weak));
extern UART_HandleTypeDef husart2 __attribute__((weak));
extern UART_HandleTypeDef husart3 __attribute__((weak));
extern UART_HandleTypeDef huart1 __attribute__((weak));
extern UART_HandleTypeDef huart2 __attribute__((weak));
extern UART_HandleTypeDef huart3 __attribute__((weak));
extern UART_HandleTypeDef huart4 __attribute__((weak));
extern UART_HandleTypeDef huart5 __attribute__((weak));

static void __attribute__((constructor)) push_uart_for_name() {
  push_pairing(&uart_for_name, "UART5", &huart5);
  push_pairing(&uart_for_name, "UART4", &huart4);
  push_pairing(&uart_for_name, "UART3", &huart3);
  push_pairing(&uart_for_name, "UART2", &huart2);
  push_pairing(&uart_for_name, "UART1", &huart1);
  push_pairing(&uart_for_name, "USART3", &husart3);
  push_pairing(&uart_for_name, "USART2", &husart2);
  push_pairing(&uart_for_name, "USART1", &husart1);
  push_pairing(&uart_for_name, "LPUART1", &hlpuart1);
}
