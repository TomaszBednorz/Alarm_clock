#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

void gpio_init();
uint8_t button_read(uint8_t button);

// Buttons defines param: @BUTTON_NUM
#define BUTTON_ACCEPT			1
#define BUTTON_LEFT				2
#define BUTTON_RIGHT			3
#define BUTTON_UP				4
#define BUTTON_DOWN				5

// GPIOs ports and pins defines
#define BUTTON_ACCEPT_PORT		GPIOA
#define BUTTON_ACCEPT_PIN		GPIO_PIN_12
#define BUTTON_LEFT_PORT		GPIOA
#define BUTTON_LEFT_PIN			GPIO_PIN_11
#define BUTTON_RIGHT_PORT		GPIOB
#define BUTTON_RIGHT_PIN		GPIO_PIN_12
#define BUTTON_UP_PORT			GPIOB
#define BUTTON_UP_PIN			GPIO_PIN_11
#define BUTTON_DOWN_PORT		GPIOC
#define BUTTON_DOWN_PIN			GPIO_PIN_8

// Button states param: @BUTTON_STATE
#define BUTTON_RELEASED			0
#define BUTTON_PUSHED			1

void gpio_init();


#endif /* INC_GPIO_H_ */
