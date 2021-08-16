#include <it.h>
#include "main.h"

extern TIM_HandleTypeDef htimer2;
extern TIM_HandleTypeDef htimer6;

extern DMA_HandleTypeDef hdma_tim3_ch1_trig;

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  while (1)
  {

  }
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {

  }
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}


/*
 * IRQ Handlers
 */

void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer2);
}

void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer6);
}

