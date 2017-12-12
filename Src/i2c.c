#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "stm32f1xx_hal.h"
#include "messages.h"
#include "i2c.h"

/*
osThreadId thread;
uint8_t data[2];

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	configASSERT(osThreadResume(thread) == osOK);
}

void task_i2c(void *i2c) {
	configASSERT(thread = osThreadGetId());

	for(;;) {
		HAL_I2C_Slave_Receive_IT(i2c, data, sizeof(data));
		configASSERT(osThreadSuspend(NULL) == osOK);

		HAL_GPIO_WritePin(GPIOB, data[0], data[1] ? SET : RESET);
	}
}
*/

osThreadId thread;
uint8_t data[2];
const int ADDR = 0x20 << 1;
const int MCP23017_GPIOA = 0x12;
const int MCP23017_IODIRA = 0x00;

uint32_t delay = 500;

bool led_strip(uint32_t delay_, Direction dir) {
	delay = delay_;
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	configASSERT(osThreadResume(thread) == osOK);
}

int res = 0;
void task_i2c(void *i2c) {
	configASSERT(thread = osThreadGetId());

	data[0] =  MCP23017_IODIRA;
	data[1] = 0x00;

	res = HAL_I2C_Master_Transmit(i2c, ADDR, data, 2, HAL_MAX_DELAY);
	//configASSERT(res == HAL_OK);

	int i = 0;
	for(;;) {
		data[0] =  MCP23017_GPIOA;
		data[1] = 1 << i;

		res = HAL_I2C_Master_Transmit(i2c, ADDR, data, 2, HAL_MAX_DELAY);

		i++;
		i &= 7;
		osDelay(delay);
		res++;
	}
}
