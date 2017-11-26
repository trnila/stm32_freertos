#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "stm32f1xx_hal.h"
#include "i2c.h"


osThreadId thread;
uint8_t data[2];
SemaphoreHandle_t i2c_sem;

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	configASSERT(osThreadResume(thread) == osOK);
}

void task_i2c(void *i2c) {
	thread = osThreadGetId();
	configASSERT(thread);

	for(;;) {
		HAL_I2C_Slave_Receive_IT(i2c, data, sizeof(data));
		configASSERT(osThreadSuspend(NULL) == osOK);

		HAL_GPIO_WritePin(GPIOB, data[0], data[1] ? SET : RESET);
	}
}
