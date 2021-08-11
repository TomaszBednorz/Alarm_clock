#include "led_strip.h"

TIM_HandleTypeDef htimer3;

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

}
