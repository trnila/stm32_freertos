#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f1xx_hal.h"
#include "../Messages/messages.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

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

uint8_t frame[20];
void task_uart(void *huart1) {
	int headerSize = 3;
	uint8_t *payload = frame + headerSize;
	GpioControlMsg msg;
	_huart1 = huart1;

	for(;;) {
		HAL_UART_Receive(huart1, frame, sizeof(frame), HAL_MAX_DELAY);
		int packetSize = (frame[1] << 8) | frame[2];

		pb_istream_t stream = pb_istream_from_buffer(payload, packetSize);
		if(!pb_decode(&stream, GpioControlMsg_fields, &msg)) {
			for(;;) {
				frame[0] = 0;
			}
		}

		xQueueSend(queue[frame[0]], &msg, portMAX_DELAY);

		// wait for ack from task
		uint8_t ackByte;
		xQueueReceive(queue2, &ackByte, portMAX_DELAY);

		// create ack frame
		/*AckMsg ack;
		ack.id = 5;
		pb_ostream_t ostream = pb_ostream_from_buffer(frame + 3, sizeof(frame) - headerSize);
		if(!pb_encode(&stream, AckMsg_fields, &ack)) {
			for(;;);
		}

		frame[0] = 255;
		frame[1] = (ostream.bytes_written & 0xFF00) >> 8;
		frame[2] = ostream.bytes_written & 0xFF;

		HAL_UART_Transmit(_huart1, frame, ostream.bytes_written, HAL_MAX_DELAY);*/
	}
}

void ack() {
	uint8_t ack = 'x';
	xQueueSend(queue2, &ack, portMAX_DELAY);
}
