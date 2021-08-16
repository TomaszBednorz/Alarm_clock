#include "buzzer.h"

TIM_HandleTypeDef htimer2;

uint8_t buzzer_melody;			// This variable storage number of buzzer melody. Param: @BUZZER_MELODY
volatile uint32_t buzzer_freq;	// This variable storage number of buzzer frequency. Param: @BUZZER_FREQUENCY


/*
 * @fn      		  - buzzer_init
 *
 * @return            - None
 *
 * @Note              - Buzzer initialization function
 */
void buzzer_init()
{
	/*
	 * Timer 2 is initialized in OC mode
	 */
	TIM_OC_InitTypeDef tim2OC_init;

	htimer2.Instance = TIM2;
	htimer2.Init.Period = 0xFFFFFFFF;
	htimer2.Init.Prescaler = 8 - 1;  // 1MHz
	if(HAL_TIM_OC_Init(&htimer2) != HAL_OK)
	{
		error_handler();
	}

	tim2OC_init.OCMode = TIM_OCMODE_TOGGLE;
	tim2OC_init.OCPolarity = TIM_OCPOLARITY_HIGH;
	tim2OC_init.Pulse = 1000;
	if(HAL_TIM_OC_ConfigChannel(&htimer2, &tim2OC_init, TIM_CHANNEL_2) != HAL_OK)
	{
		error_handler();
	}

	/*
	 * Basic setting of buzzer melody and frequency
	 */
	buzzer_melody = BUZZER_MELODY_1;
	buzzer_freq = BUZZER_250HZ;
}

/*
 * @fn      		  - buzzer_set_melody
 *
 * @param[in]         - melody - param: @BUZZER_MELODY
 *
 * @return            - None
 *
 * @Note              - Set buzzer melody
 */
void buzzer_set_melody(uint8_t melody)
{
	buzzer_melody = melody;
}

/*
 * @fn      		  - buzzer_start
 *
 * @return            - None
 *
 * @Note              - Buzzer start buzz
 */
void buzzer_start(void)
{
	if(HAL_TIM_OC_Start_IT(&htimer2, TIM_CHANNEL_2) != HAL_OK)
	{
		error_handler();
	}
}

/*
 * @fn      		  - buzzer_stop
 *
 * @return            - None
 *
 * @Note              - Buzzer stop buzz
 */
void buzzer_stop(void)
{
	if(HAL_TIM_OC_Stop_IT(&htimer2, TIM_CHANNEL_2) != HAL_OK)
	{
		error_handler();
	}
}

/*
 * This callback is responsible for different frequency of buzzer melody (buzzer_freq variable inside)
 */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint32_t crr_content;

	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	{
		crr_content = HAL_TIM_ReadCapturedValue(&htimer2, TIM_CHANNEL_2);
		__HAL_TIM_SET_COMPARE(&htimer2, TIM_CHANNEL_2, crr_content + buzzer_freq);
	}

}

