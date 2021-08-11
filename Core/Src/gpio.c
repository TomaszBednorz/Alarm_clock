#include "gpio.h"


void gpio_init()
{
	GPIO_InitTypeDef GPIO_buttons = {0};
	/*
	 * PA12 --> BUTTON_ACCEPT
	 * PA11 --> LEFT_BUTTON
	 * PB12 --> RIGHT_BUTTON
	 * PB11 --> UP_BUTTON
	 * PC8  --> DOWN_BUTTON
	 */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_buttons.Pin = BUTTON_ACCEPT_PIN;
	GPIO_buttons.Pull = GPIO_NOPULL;
	GPIO_buttons.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_buttons.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(BUTTON_ACCEPT_PORT, &GPIO_buttons);

	GPIO_buttons.Pin = BUTTON_LEFT_PIN;
	HAL_GPIO_Init(BUTTON_LEFT_PORT, &GPIO_buttons);

	GPIO_buttons.Pin = BUTTON_RIGHT_PIN;
	HAL_GPIO_Init(BUTTON_RIGHT_PORT, &GPIO_buttons);

	GPIO_buttons.Pin = BUTTON_UP_PIN;
	HAL_GPIO_Init(BUTTON_UP_PORT, &GPIO_buttons);

	GPIO_buttons.Pin = BUTTON_DOWN_PIN;
	HAL_GPIO_Init(BUTTON_DOWN_PORT, &GPIO_buttons);

}
