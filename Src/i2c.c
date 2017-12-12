#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "stm32f1xx_hal.h"
#include "messages.h"
#include "i2c.h"

EventGroupHandle_t eventGroup;
uint8_t data[2];
uint32_t delay = 500;
bool running = true;
int led = 0;
int res = 0;

const int ADDR = 0x20 << 1;
const int MCP23017_GPIOA = 0x12;
const int MCP23017_IODIRA = 0x00;

bool led_strip(uint32_t delay_, Direction dir) {
	delay = delay_;

	xEventGroupSetBits(eventGroup, 0x1);
	taskYIELD();
}

bool led_ctrl(Ctrl ctrl) {
	if(ctrl == Ctrl_pause) {
		running = false;
	} else {
		running = true;

		if(ctrl == Ctrl_restart) {
			led = 0;
		}
	}

	xEventGroupSetBits(eventGroup, 0x1);
	taskYIELD();
}

void task_i2c(void *i2c) {
    eventGroup = xEventGroupCreate();
    configASSERT(eventGroup != NULL);

	// setup all GPIO pins as OUT
	data[0] =  MCP23017_IODIRA;
	data[1] = 0x00;
	while(HAL_I2C_Master_Transmit(i2c, ADDR, data, 2, HAL_MAX_DELAY) != HAL_OK) {
		osDelay(10);
	}

	for(;;) {
		EventBits_t bits = xEventGroupWaitBits(eventGroup, 0x07, pdTRUE, pdFALSE, running ? delay : portMAX_DELAY);

		data[0] =  MCP23017_GPIOA;
		data[1] = running ? 1 << led : 0x00;

		res = HAL_I2C_Master_Transmit(i2c, ADDR, data, 2, HAL_MAX_DELAY);

		led++;
		led &= 7;
	}
}
