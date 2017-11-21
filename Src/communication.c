#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f1xx_hal.h"
#include "../Messages/messages.pb.h"
#include "pb_decode.h"

#define MESSAGES_MAX 2

QueueHandle_t queue[MESSAGES_MAX];
QueueHandle_t queue2;
void *_huart1;

void msg_init() {
	for(int i = 0; i < MESSAGES_MAX; i++) {
		queue[i] = xQueueCreate(1, 20);
	}

	queue2 = xQueueCreate(1, 10);
}

void msg_recv(int type, void* msg) {
	xQueueReceive(queue[type], msg, portMAX_DELAY);
}

void task_uart(void *huart1) {
	uint8_t rcv[20];
	GpioControlMsg msg;
	_huart1 = huart1;

	for(;;) {
		uint8_t header[3];
		HAL_UART_Receive(huart1, header, sizeof(header), HAL_MAX_DELAY);
		int packetSize = (header[1] << 8) | header[2];

		// ready message body
		HAL_UART_Receive(huart1, rcv, packetSize, HAL_MAX_DELAY);
		pb_istream_t stream = pb_istream_from_buffer(rcv, packetSize);
		if(!pb_decode(&stream, GpioControlMsg_fields, &msg)) {
			for(;;);
		}

		xQueueSend(queue[header[0]], &msg, portMAX_DELAY);
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
