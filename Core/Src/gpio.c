#include "gpio.h"


void gpio_init()
{
	GPIO_InitTypeDef GPIO_buttons = {0};
	/*
	 * PA12 --> BUTTON_ACCEPT
	 */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_buttons.Pin = BUTTON_ACCEPT_PIN;
	GPIO_buttons.Pull = GPIO_NOPULL;
	GPIO_buttons.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_buttons.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(BUTTON_ACCEPT_PORT, &GPIO_buttons);

}
