#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f1xx_hal.h"
#include "../Messages/messages.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

#define MESSAGES_MAX 3

QueueHandle_t queue[MESSAGES_MAX];
QueueHandle_t queue2;
void *_huart1;

const int headerSize = 3;
uint8_t frame[20];
uint8_t msg[20];
const pb_field_t *types[] = {
		 GpioControlMsg_fields,
		 ReverseMsg_fields,
		 PingMsg_fields
};

void msg_init() {
	for(int i = 0; i < MESSAGES_MAX; i++) {
		queue[i] = xQueueCreate(1, 20);
	}

	queue2 = xQueueCreate(1, 10);
}

void msg_recv(int type, void* msg) {
	xQueueReceive(queue[type], msg, portMAX_DELAY);
}

void send(int type, void *data) {
	pb_ostream_t ostream = pb_ostream_from_buffer(frame + headerSize, sizeof(frame) - headerSize);
	if(!pb_encode(&ostream, types[type], data)) {
		for(;;) {
			frame[19] = 'f';
		}
	}

	frame[0] = type;
	frame[1] = (ostream.bytes_written & 0xFF00) >> 8;
	frame[2] = ostream.bytes_written & 0xFF;

	HAL_UART_Transmit(_huart1, frame, headerSize + ostream.bytes_written, HAL_MAX_DELAY);
}

void task_uart(void *huart1) {
	uint8_t *payload = frame + headerSize;
	_huart1 = huart1;

	for(;;) {
		if(HAL_UART_Receive(huart1, frame, sizeof(frame), 1000) != HAL_OK) {
			continue;
		}
		int packetSize = (frame[1] << 8) | frame[2];

		// unknown message arrived
		if(frame[0] >= MESSAGES_MAX) {
			continue;
		}

		pb_istream_t stream = pb_istream_from_buffer(payload, packetSize);
		if(!pb_decode(&stream, types[frame[0]], &msg)) {
			continue;
		}

		xQueueSend(queue[frame[0]], &msg, portMAX_DELAY);

		// wait for ack from task
		uint8_t ackByte;
		xQueueReceive(queue2, &ackByte, portMAX_DELAY);
	}
}

void ack() {
	uint8_t ack = 'x';
	xQueueSend(queue2, &ack, portMAX_DELAY);
}
