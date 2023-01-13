/*
 * hal_i2c.c
 *
 *  Created on: 13 Jan 2023
 *      Author: RoyRatcliffe
 */

#include "stm32l4xx.h"

#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t I2C1MasterTaskHandle __attribute__((weak));
extern TaskHandle_t I2C2MasterTaskHandle __attribute__((weak));
extern TaskHandle_t I2C3MasterTaskHandle __attribute__((weak));

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	TaskHandle_t xTaskToNotify;
	if (hi2c->Instance == I2C1)
		xTaskToNotify = I2C1MasterTaskHandle;
	if (hi2c->Instance == I2C2)
		xTaskToNotify = I2C2MasterTaskHandle;
	if (hi2c->Instance == I2C3)
		xTaskToNotify = I2C3MasterTaskHandle;
	else
		xTaskToNotify = NULL;
	if (xTaskToNotify)
		xTaskNotify(xTaskToNotify, 1UL << 0U, eSetBits);
}
