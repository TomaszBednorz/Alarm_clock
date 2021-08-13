#include "gpio.h"

uint8_t button_read(uint8_t button);

void gpio_init()
{
	GPIO_InitTypeDef GPIO_buttons = {0};
	GPIO_InitTypeDef GPIO_led = {0};
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
	/*
	 * PA6 --> RED_LED
	 */
	GPIO_led.Pin = RED_LED_PIN;
	GPIO_led.Pull = GPIO_NOPULL;
	GPIO_led.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_led.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(RED_LED_PORT, &GPIO_led);
}

/*
 * @fn      		  - button_read
 *
 * @param[in]         - button - param: @BUTTON_NUM
 *
 * @return            - param: @BUTTON_STATE
 *
 * @Note              - This function read state from GPIOs
 */
uint8_t button_read(uint8_t button)
{
	if(button == BUTTON_ACCEPT)
	{
		if(HAL_GPIO_ReadPin(BUTTON_ACCEPT_PORT, BUTTON_ACCEPT_PIN) == GPIO_PIN_RESET)
		{
			return BUTTON_PUSHED;
		}
	}
	else if(button == BUTTON_LEFT)
	{
		if(HAL_GPIO_ReadPin(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN) == GPIO_PIN_RESET)
		{
			return BUTTON_PUSHED;
		}
	}
	else if(button == BUTTON_RIGHT)
	{
		if(HAL_GPIO_ReadPin(BUTTON_RIGHT_PORT, BUTTON_RIGHT_PIN) == GPIO_PIN_RESET)
		{
			return BUTTON_PUSHED;
		}
	}
	else if(button == BUTTON_UP)
	{
		if(HAL_GPIO_ReadPin(BUTTON_UP_PORT, BUTTON_UP_PIN) == GPIO_PIN_RESET)
		{
			return BUTTON_PUSHED;
		}
	}
	else if(button == BUTTON_DOWN)
	{
		if(HAL_GPIO_ReadPin(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN) == GPIO_PIN_RESET)
		{
			return BUTTON_PUSHED;
		}
	}

	return BUTTON_RELEASED;
}


