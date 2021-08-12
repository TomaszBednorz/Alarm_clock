#include "led_strip.h"

TIM_HandleTypeDef htimer3;

static uint8_t buffer[RESET_CODE_LEN + LED_RGB_COLOR_LEN * LED_NUM + 1] = {0};  // High state of line at the end of transmission

/*
 * @fn      		  - led_init
 *
 * @return            - None
 *
 * @Note              - Initialize led strip
 */
void led_init(void)
{
	TIM_ClockConfigTypeDef clock_config = {0};
	TIM_OC_InitTypeDef tim3OC_init = {0};

	htimer3.Instance = TIM3;
	htimer3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer3.Init.Period = 49;
	if (HAL_TIM_Base_Init(&htimer3) != HAL_OK)
	{
	error_handler();
	}

	clock_config.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htimer3, &clock_config) != HAL_OK)
	{
	  error_handler();
	}

	if (HAL_TIM_PWM_Init(&htimer3) != HAL_OK)
	{
	  error_handler();
	}

	tim3OC_init.OCMode = TIM_OCMODE_PWM1;
	tim3OC_init.OCPolarity = TIM_OCPOLARITY_HIGH;
	if (HAL_TIM_PWM_ConfigChannel(&htimer3, &tim3OC_init, TIM_CHANNEL_1) != HAL_OK)
	{
	  error_handler();
	}
	HAL_TIM_MspPostInit(&htimer3);

	for(int i = 0; i < RESET_CODE_LEN; i++)
	{
		buffer[i] = CODE_RESET_HIGH;
	}

	buffer[RESET_CODE_LEN + LED_RGB_COLOR_LEN * LED_NUM + 1] = LINE_HIGH;

	if(HAL_TIM_Base_Start(&htimer3) != HAL_OK)
	{
		error_handler();
	}
}

/*
 * @fn      		  - led_update_color
 *
 * @param[in]         - led - number of led in strip: 0 to 7
 * @param[in]         - red - intensity of red led in RGB: 0 to 255
 * @param[in]         - green - intensity of green led in RGB: 0 to 255
 * @param[in]         - blue - intensity of blue led in RGB: 0 to 255
 *
 * @return            - None
 *
 * @Note              - Update color of leds in strip
 */
void led_update_color(uint8_t led, uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t mask = 0x80;  // 10000000 in binary

	if(led < LED_NUM)
	{
		for(int byte_size = 0; byte_size < 8; byte_size++)
		{
			if(green & mask)
			{
				buffer[RESET_CODE_LEN + led * LED_RGB_COLOR_LEN + GREEN_COLOR_OFFSET + byte_size] = CODE_1_HIGH;
			}
			else
			{
				buffer[RESET_CODE_LEN + led * LED_RGB_COLOR_LEN + GREEN_COLOR_OFFSET + byte_size] = CODE_0_HIGH;
			}

			if(red & mask)
			{
				buffer[RESET_CODE_LEN + led * LED_RGB_COLOR_LEN + RED_COLOR_OFFSET + byte_size] = CODE_1_HIGH;
			}
			else
			{
				buffer[RESET_CODE_LEN + led * LED_RGB_COLOR_LEN + RED_COLOR_OFFSET + byte_size] = CODE_0_HIGH;
			}

			if(blue & mask)
			{
				buffer[RESET_CODE_LEN + led * LED_RGB_COLOR_LEN + BLUE_COLOR_OFFSET + byte_size] = CODE_1_HIGH;
			}
			else
			{
				buffer[RESET_CODE_LEN + led * LED_RGB_COLOR_LEN + BLUE_COLOR_OFFSET + byte_size] = CODE_0_HIGH;
			}

			mask >>= 1;
		}
	}
}

/*
 * @fn      		  - led_send_color
 *
 * @return            - None
 *
 * @Note              - Send color set in led_update_color to led strip
 */
void led_send_color()
{
	if(HAL_TIM_PWM_Start_DMA(&htimer3, TIM_CHANNEL_1, (uint32_t*)buffer, sizeof(buffer)) != HAL_OK)
	{
		error_handler()	;
	}
}


