#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "../Messages/messages.pb.h"

void task_reverse(void *param) {
	GpioControlMsg msg;
	for(;;) {
		msg_recv(1, &msg);

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

		osDelay(1);
		ack();
	}
}
