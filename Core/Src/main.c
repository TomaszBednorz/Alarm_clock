#include "main.h"

volatile uint8_t IT_every_1s = 0; // Interrupt every 1s variable

// Variables needed to initialization
extern lcd_display display;
extern RTC_time time;
extern RTC_date date;


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
	DMA_init();
	led_init();
	interrupt_1s_init();
	// Basic initializations - END

	// Default initialization - START
	display.backlight = 1;
	date.day = 1;
	date.date = 1;
	date.month = 1;
	date.year = 10;

	rtc_set_time(&time);
	rtc_set_date(&date);

	time_date_actualization(STRICT_UPDATE_TRUE);

	// Default initialization - END





	//	buzzer_service();





	while (1)
	{

//		uint8_t r = rand();
//		uint8_t g = rand();
//		uint8_t b = rand();
//
//		for (int led = 0; led < 8; led++)
//		{
//			led_update_color(led, r, g, b);
//			led_send_color();
//			HAL_Delay(100);
//		}

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


