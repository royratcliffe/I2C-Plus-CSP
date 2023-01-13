/*
 * i2c_master.c
 *
 *  Created on: 13 Jan 2023
 *      Author: RoyRatcliffe
 */

#include <limits.h>

#include <csp/csp.h>

#include "FreeRTOS.h"
#include "task.h"

#include "stm32l4xx_hal.h"

/**
 * The server task tries not to hold two complete packets simultaneously, even though it handles a request and reply packet.
 */
void vI2CMasterTask(void *pvParameters) {
	I2C_HandleTypeDef *hI2C = (I2C_HandleTypeDef*) pvParameters;
	csp_socket_t socket = { 0 };
	csp_bind(&socket, 10);
	csp_listen(&socket, 5);
	for (;;) {
		csp_conn_t *conn = csp_accept(&socket, 10000);
		if (conn == NULL)
			continue;
		csp_packet_t *packet;
		while ((packet = csp_read(conn, 100))) {
			if (packet->length >= 2) {
				uint16_t uDevAddress = packet->data[0] << 1;
				uint32_t ulNotified;
				while (HAL_I2C_Master_Transmit_IT(hI2C, uDevAddress,
						packet->data + 2, packet->length - 2) != HAL_OK)
					vTaskDelay(pdMS_TO_TICKS(1));
				xTaskNotifyWait(0L, ULONG_MAX, &ulNotified, portMAX_DELAY);
				size_t length = packet->data[1];
				csp_buffer_free(packet);
				packet = csp_buffer_get(length);
				if (length) {
					while (HAL_I2C_Master_Receive_IT(hI2C, uDevAddress,
							packet->data, length) != HAL_OK)
						vTaskDelay(pdMS_TO_TICKS(1));
					xTaskNotifyWait(0L, ULONG_MAX, &ulNotified, portMAX_DELAY);
				}
				csp_send(conn, packet);
			} else {
				csp_buffer_free(packet);
			}
		}
		csp_close(conn);
	}
}
