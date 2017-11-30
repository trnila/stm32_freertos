#include "FreeRTOS.h"
#include "task.h"
#include "stm32f1xx_hal.h"
#include "messages_server.h"


GPIO_TypeDef* mapPort(Port port) {
	switch(port) {
	case GPIO_A:
		return GPIOA;
	case GPIO_B:
		return GPIOB;
	case GPIO_C:
		return GPIOC;
	}

	configASSERT(0);
}

uint8_t set_led(Port port, uint8_t led, bool on) {
	HAL_GPIO_WritePin(mapPort(port), led, on ? SET : RESET);
	return 255;
}

void task_uart(void *huart1) {
	erpc_server_init(erpc_transport_cmsis_uart_init(huart1), erpc_mbf_static_init());
	erpc_add_service_to_server(create_IO_service());

	for(;;) {
		erpc_server_run();
	}
	configASSERT(0);
}
