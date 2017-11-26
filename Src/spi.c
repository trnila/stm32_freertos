#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "stm32f1xx_hal.h"
#include "spi.h"

static osThreadId thread;
static uint8_t data[3];

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
	configASSERT(osThreadResume(thread) == osOK);
}

void task_spi(void *spi) {
	thread = osThreadGetId();
	configASSERT(thread);

	for(;;) {
		HAL_SPI_Receive_IT(spi, data, sizeof(data));
		configASSERT(osThreadSuspend(NULL) == osOK);

		HAL_GPIO_WritePin(numToPort(data[0]), data[1], data[2] ? SET : RESET);
	}
}
