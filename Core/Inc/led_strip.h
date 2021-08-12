#ifndef INC_LED_STRIP_H_
#define INC_LED_STRIP_H_

#include "main.h"

void led_init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim); // Fcn in msp.c

#endif /* INC_LED_STRIP_H_ */
