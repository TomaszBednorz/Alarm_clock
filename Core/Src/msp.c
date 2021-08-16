#include "main.h"

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	GPIO_InitTypeDef GPIO_i2c1 = {0};
	GPIO_InitTypeDef GPIO_i2c2 = {0};

	if(hi2c->Instance == I2C1)
	{
		/*
		 * PB6 --> I2C1_SCL
		 * PB7 --> I2C1_SDA
		 */
		__HAL_RCC_I2C1_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		GPIO_i2c1.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_i2c1.Pull = GPIO_NOPULL;
		GPIO_i2c1.Speed = GPIO_SPEED_FREQ_MEDIUM;
		GPIO_i2c1.Mode = GPIO_MODE_AF_OD;
		GPIO_i2c1.Alternate = GPIO_AF1_I2C1;
		HAL_GPIO_Init(GPIOB, &GPIO_i2c1);
	}

	if(hi2c->Instance == I2C2)
	{
		/*
		 * PB13 --> I2C2_SCL
		 * PB14 --> I2C2_SDA
		 */

		__HAL_RCC_I2C2_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		GPIO_i2c2.Pin = GPIO_PIN_13 | GPIO_PIN_14;
		GPIO_i2c2.Pull = GPIO_PULLUP;
		GPIO_i2c2.Speed = GPIO_SPEED_FREQ_MEDIUM;
		GPIO_i2c2.Mode = GPIO_MODE_AF_OD;
		GPIO_i2c2.Alternate = GPIO_AF5_I2C2;
		HAL_GPIO_Init(GPIOB, &GPIO_i2c2);
	}
}

void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_tim2;

	// Enable the peripheral clock for timer2 peripheral
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*
	 *  PA5 --> TIM2_CH2
	 */

	GPIO_tim2.Pin = GPIO_PIN_1;
	GPIO_tim2.Mode = GPIO_MODE_AF_PP;
	GPIO_tim2.Pull = GPIO_NOPULL;
	GPIO_tim2.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_tim2.Alternate = GPIO_AF2_TIM2;
	HAL_GPIO_Init(GPIOA, &GPIO_tim2);


	// NVIC settings
	HAL_NVIC_SetPriority(TIM2_IRQn, 3, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM6)
  {
	__HAL_RCC_TIM6_CLK_ENABLE();

	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  }
}
