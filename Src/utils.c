#include "utils.h"

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
