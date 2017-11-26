#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "pb.h"
#include "pb_encode.h"
#include "../Messages/messages.pb.h"

PrintMsg printMsg;

void task_handle_gpio(void *param) {
	GpioControlMsg msg;
	for(;;) {
		msg_recv(0, &msg);

		GPIO_TypeDef* gpio;
		if(msg.port == GpioControlMsg_Port_PortA) {
			gpio = GPIOA;
		} else if(msg.port == GpioControlMsg_Port_PortB) {
			gpio = GPIOB;
		} else if(msg.port == GpioControlMsg_Port_PortC) {
			gpio = GPIOC;
		} else {
			for(;;);
		}


		HAL_GPIO_WritePin(gpio, msg.pin, msg.state);

		ack();
	}
}

void task_ping(void* param) {
	PingMsg msg;
	for(;;) {
		msg_recv(2, &msg);

		send(2, &msg);

		sprintf(printMsg.msg, "received ping seq: %d", msg.seq);
		send(3, &printMsg);

		ack();
	}
}

GPIO_TypeDef *numToPort(int n) {
	switch(n) {
	case 0:
		return GPIOA;
	case 1:
		return GPIOB;
	case 2:
		return GPIOC;
	}

	return NULL;
}

/*
void task_reverse(void *param) {
	ReverseMsg msg;
	for(;;) {
		msg_recv(1, &msg);

		for(int i = 0; i < strlen(msg.name); i++) {
			msg.name[i] = 'a' + i;
		}

		uint8_t buffer[ReverseMsg_size];
		pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
		if(!pb_encode(&stream, ReverseMsg_fields, &msg)) {
			for(;;);
		}

		msg_send(1, stream.bytes_written, buffer);
	}
}
*/
