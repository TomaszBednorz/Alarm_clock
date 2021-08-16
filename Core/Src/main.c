#include "main.h"

volatile uint8_t IT_every_1s = 0; // Interrupt every 1s variable

// Variables needed to initialization
extern lcd_display display;
extern RTC_time time;
extern RTC_date date;
extern RTC_alarm alarm_1;
extern RTC_alarm alarm_2;

int main(void)
{
	// Basic initializations - START
	HAL_Init();
	clock_configuration();

	i2c1_init();
	i2c2_init();
	gpio_init();
	buzzer_init();
	lcd_init(&display);
	lcd_clear_and_update(&display);
	interrupt_1s_init();
	// Basic initializations - END

	// Default initialization - START

	HAL_GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, GPIO_PIN_RESET);  //Disable RED LED

	// Default clock parameters
	display.backlight = 1;
	date.day = DS3231_RTC_MONDAY;
	date.date = 1;
	date.month = DS3231_RTC_JANUARY;
	date.year = 10;

	alarm_1.day = DS3231_RTC_MONDAY;
	alarm_2.day = DS3231_RTC_MONDAY;

	rtc_set_time(&time);
	rtc_set_date(&date);
	time_date_actualization(STRICT_UPDATE_TRUE);
	rtc_alarm_disable(DS3231_RTC_ALARM_1);
	rtc_alarm_disable(DS3231_RTC_ALARM_2);
	// Default initialization - END



	while (1)
	{
		uint32_t current_time = HAL_GetTick();
		while(button_read(BUTTON_ACCEPT) == BUTTON_PUSHED)
		{
			if(current_time + 500 < HAL_GetTick()) // BUTTON_ACCEPT --> main_menu()
			{
				main_menu();
				current_time = HAL_GetTick();
			}
		}

		if(IT_every_1s)
		{
			time_date_actualization(STRICT_UPDATE_FALSE);
			alarm_service();
			IT_every_1s = 0;
		}

	}
}


/*
 * Callback will be trigger every 1s (set by timer 6)
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		IT_every_1s = 1;
	}
}


