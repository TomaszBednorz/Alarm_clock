#include "basic_functionalities.h"

TIM_HandleTypeDef htimer6;

/*
 *  HSI 40MHz
 */
void clock_configuration(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  // RCC Oscillator init
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL5;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
	  error_handler();
  }

  // CPU, AHB and APB buses clocks init
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
	  error_handler();
  }
}

/*
 * Interrupt every 1s triggered by timer 6
 */
void interrupt_1s_init(void)
{
	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 3999;
	htimer6.Init.Period = 9999;
	if(HAL_TIM_Base_Init(&htimer6) != HAL_OK)
	{
		error_handler();
	}

	if(HAL_TIM_Base_Start_IT(&htimer6) != HAL_OK)
	{
		error_handler();
	}
}

void error_handler(void)
{
  while (1)
  {
	  // Infinity loop
  }
}
