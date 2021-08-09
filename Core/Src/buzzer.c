#include "buzzer.h"

TIM_HandleTypeDef htimer2;

uint8_t buzzer_melody;

volatile uint8_t tim2_OC_IT = 0;
volatile uint32_t buzzer_freq;

static void buzzer_start(void);
static void buzzer_stop(void);

/*
 * @fn      		  - buzzer_init
 *
 * @return            - None
 *
 * @Note              - Buzzer init function
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
	buzzer_melody = BUZZER_MELODY_1;
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
 * @fn      		  - buzzer_service
 *
 * @return            - None
 *
 * @Note              - Function which service buzzer
 */
void buzzer_service(void)
{
	buzzer_freq = BUZZER_500HZ;

	buzzer_start();

	uint32_t time = HAL_GetTick();

	while(HAL_GPIO_ReadPin(BUTTON_ACCEPT_PORT, BUTTON_ACCEPT_PIN) != GPIO_PIN_SET)
	{
		if(time + 7500 <= HAL_GetTick())
		{
			buzzer_freq = BUZZER_2000HZ;
		}
		else if(time + 5000 <= HAL_GetTick())
		{
			buzzer_freq = BUZZER_500HZ;
		}
		else if(time + 2500 <= HAL_GetTick())
		{
			buzzer_freq = BUZZER_2000HZ;
		}
	}
	buzzer_stop();
}




static void buzzer_start(void)
{
	if(HAL_TIM_OC_Start_IT(&htimer2, TIM_CHANNEL_2) != HAL_OK)
	{
		error_handler();
	}
}

static void buzzer_stop(void)
{
	if(HAL_TIM_OC_Stop_IT(&htimer2, TIM_CHANNEL_2) != HAL_OK)
	{
		error_handler();
	}
}







void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint32_t crr_content;

	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	{
		crr_content = HAL_TIM_ReadCapturedValue(&htimer2, TIM_CHANNEL_2);
		__HAL_TIM_SET_COMPARE(&htimer2, TIM_CHANNEL_2, crr_content + buzzer_freq);
	}

}

