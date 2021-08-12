#include "main.h"

volatile uint8_t IT_every_1s = 0; // Interrupt every 1s variable

// Display variables
lcd_display display;
char display_line_1[17];
char display_line_2[17];

// RTC variables
RTC_time time = {0};
RTC_date date = {0};
RTC_alarm alarm_1 = {0};
RTC_alarm alarm_2 = {0};

// Buzzer variables
extern uint8_t buzzer_melody;
extern volatile uint32_t buzzer_freq;

uint8_t current_state;

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

	rtc_set_time(&time);
	rtc_set_date(&date);


	time_date_actualization(STRICT_UPDATE_FALSE);

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

		uint32_t time = HAL_GetTick();
		while(button_read(BUTTON_ACCEPT) == BUTTON_PUSHED)
		{
			if(time + 500 < HAL_GetTick()) // BUTTON_ACCEPT --> main_menu()
			{
				current_state = 0;
				main_menu();
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
 * @fn      		  - time_date_actualization
 *
 * @param[in]         - strict_update - param: @STRICT_ACTUALIZATION
 *
 * @return            - None
 *
 * @Note              - This function actualize time from rtc on lcd. Time is always updated, but date only when
 * 						strict_update is true or when second in time is 0.
 */
void time_date_actualization(bool strict_update)
{
	static char* rtc_month_roman[12] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII" };
	static char* rtc_day_str[7] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };

	time = rtc_get_time();
	date = rtc_get_date();

	if(time.seconds == 0 || strict_update == true)
	{
		if(date.year < 10)
		{
			sprintf(display_line_1, "%d %s 200%dr", date.date, rtc_month_roman[date.month - 1], date.year);
		}
		else
		{
			sprintf(display_line_1, "    %d.%s.20%dr", date.date, rtc_month_roman[date.month - 1], date.year);
		}
		sprintf(display.line_1st, display_line_1);
	}

	char hours[4] = {0};
	char minutes[4] = {0};
	char seconds[3] = {0};

	if(time.hours < 10)
	{
		sprintf(hours, "0%d:", time.hours);
	}
	else
	{
		sprintf(hours, "%d:", time.hours);
	}

	if(time.minutes < 10)
	{
		sprintf(minutes, "0%d:", time.minutes);
	}
	else
	{
		sprintf(minutes, "%d:", time.minutes);
	}

	if(time.seconds < 10)
	{
		sprintf(seconds, "0%d", time.seconds);
	}
	else
	{
		sprintf(seconds, "%d", time.seconds);
	}

	memset(display_line_2,0,strlen(display_line_2));

	strcat(display_line_2, hours);
	strcat(display_line_2, minutes);
	strcat(display_line_2, seconds);
	strcat(display_line_2, "     ");
	strcat(display_line_2, rtc_day_str[date.day - 1]);


	sprintf(display.line_2nd, display_line_2);

	if(time.seconds == 0)
	{
		lcd_clear_and_update(&display);
	}
	else
	{
		lcd_update(&display, LINE_SECOND);
	}

}

void main_menu(void)
{
	bool end_main_menu_loop = false;

	static char* menu_options[6] = {"<-  SET TIME  ->", "<- SET ALARM1 ->", "<- SET ALARM2 ->", "<- SET BUZZER ->",
								   "<-  SET  LED  ->", "<-    EXIT    ->"};

	sprintf(display.line_1st, "   MAIN  MENU   ");
	sprintf(display.line_2nd, menu_options[current_state]);
	lcd_clear_and_update(&display);

	while(1)
	{
		if(button_read(BUTTON_RIGHT) == BUTTON_PUSHED)
		{
			if(current_state <= 4)
			{
				current_state++;
				sprintf(display.line_2nd, menu_options[current_state]);
				lcd_update(&display, LINE_SECOND);
				HAL_Delay(100); // debouncing protection
			}
		}

		if(button_read(BUTTON_LEFT) == BUTTON_PUSHED)
		{
			if(current_state >= 1)
			{
				current_state--;
				sprintf(display.line_1st, "   MAIN  MENU   ");
				sprintf(display.line_2nd, menu_options[current_state]);
				lcd_update(&display, LINE_SECOND);
				HAL_Delay(100); // debouncing protection
			}
		}

		if(button_read(BUTTON_ACCEPT) == BUTTON_PUSHED)
		{
			switch (current_state) {
				case STATE_TIME:

					break;
				case STATE_ALARM1:

					break;
				case STATE_ALARM2:

					break;
				case STATE_BUZZER:

					break;
				case STATE_LED:

					break;
				case STATE_EXIT:
					end_main_menu_loop = true;
					break;
				default:
					break;
			}
		}

		if(end_main_menu_loop == true)
		{
			HAL_Delay(100); // debouncing protection
			break;
		}

	}
}

void buzzer_service(void)
{
	buzzer_freq = BUZZER_250HZ;

	buzzer_start();

	uint32_t time = HAL_GetTick();

	while(1)
	{
		if(HAL_GPIO_ReadPin(BUTTON_ACCEPT_PORT, BUTTON_ACCEPT_PIN) == GPIO_PIN_RESET)
		{
			break;
		}
		else if(time + 4000 <= HAL_GetTick())
		{
			buzzer_freq = BUZZER_250HZ;
			time = HAL_GetTick();
		}
		else if(time + 3000 <= HAL_GetTick())
		{
			if(buzzer_melody == BUZZER_MELODY_3)
			{
				buzzer_freq = BUZZER_2000HZ;
			}
			else if(buzzer_melody == BUZZER_MELODY_2)
			{
				buzzer_freq = BUZZER_1000HZ;
			}
		}
		else if(time + 2000 <= HAL_GetTick())
		{
			if(buzzer_melody == BUZZER_MELODY_3 || buzzer_melody == BUZZER_MELODY_1)
			{
				buzzer_freq = BUZZER_1000HZ;
			}
			else if(buzzer_melody == BUZZER_MELODY_2)
			{
				buzzer_freq = BUZZER_250HZ;
			}
		}
		else if(time + 1000 <= HAL_GetTick())
		{
			if(buzzer_melody == BUZZER_MELODY_3)
			{
				buzzer_freq = BUZZER_500HZ;
			}
			else if(buzzer_melody == BUZZER_MELODY_2)
			{
				buzzer_freq = BUZZER_1000HZ;
			}
		}

	}
	buzzer_stop();
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


