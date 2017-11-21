#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f1xx_hal.h"
#include "../Messages/messages.pb.h"
#include "pb_decode.h"

QueueHandle_t queue;
QueueHandle_t queue2;
void *_huart1;

void msg_init() {
	queue = xQueueCreate(1, 20);
	queue2 = xQueueCreate(1, 10);
}

void msg_recv(int type, void* msg) {
	xQueueReceive(queue, msg, portMAX_DELAY);
}

void task_uart(void *huart1) {
	uint8_t rcv[20];
	GpioControlMsg msg;

	_huart1 = huart1;

	uint8_t test[] = "ahoj";
	HAL_UART_Transmit(huart1, test, strlen(test), HAL_MAX_DELAY);

	int packetSize = 6;
	for(;;) {
		HAL_UART_Receive(huart1, rcv, 8 + packetSize, HAL_MAX_DELAY);

		pb_istream_t stream = pb_istream_from_buffer(rcv + 8, packetSize);
		if(!pb_decode(&stream, GpioControlMsg_fields, &msg)) {
			for(;;);
		}

		xQueueSend(queue, &msg, portMAX_DELAY);
		taskYIELD();

		uint8_t ack;
		xQueueReceive(queue2, &ack, portMAX_DELAY);
		HAL_UART_Transmit(_huart1, &ack, 1, HAL_MAX_DELAY);
	}
}

void ack() {
	uint8_t ack = 'x';
	xQueueSend(queue2, &ack, portMAX_DELAY);
}
