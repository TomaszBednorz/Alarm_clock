#include "interface.h"

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
uint8_t current_substate;

static char* rtc_month_roman[12] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII" };
static char* rtc_day_str[7] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };




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
	time = rtc_get_time();
	date = rtc_get_date();

	if(time.seconds == 0 || strict_update == true)
	{
		sprintf(display_line_1, "%d.%s.20%dr", date.date, rtc_month_roman[date.month - 1], date.year);
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
	current_state = 0;

	static char* menu_options[6] = {"<-  SET TIME  ->", "<- SET ALARM1 ->", "<- SET ALARM2 ->", "<- SET BUZZER ->",
								   "<-  SET  LED  ->", "<-    EXIT    ->"};

	sprintf(display.line_1st, "   MAIN  MENU   ");
	sprintf(display.line_2nd, menu_options[current_state]);
	lcd_clear_and_update(&display);

	HAL_Delay(200); // debouncing protection

	while(end_main_menu_loop != true)
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
				case STATE_DATE_TIME:
					set_date_time();
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
	}
}

void set_date_time(void)
{
	date.date = 1;
	date.month = DS3231_RTC_JANUARY;
	date.year = 10;
	date.day = DS3231_RTC_SUNDAY;

	sprintf(display.line_1st, "    SET DATE    ");
	sprintf(display.line_2nd, "%d.%s.20%dr %s", date.date, rtc_month_roman[date.month - 1], date.year, rtc_day_str[date.day - 1]);
	lcd_clear_and_update(&display);

	current_substate = STATE_DATE;

	bool end_date_time_loop = false;

	HAL_Delay(200); // debouncing protection

	while(end_date_time_loop != true)
	{
		if(button_read(BUTTON_UP) == BUTTON_PUSHED)
		{
			switch (current_substate) {
				case STATE_DATE:
					if(date.date < 31)
					{
						date.date++;
					}
					else if(date.date == 31)
					{
						date.date = 1;
					}
					break;
				case STATE_MONTH:
					if(date.month < 12)
					{
						date.month++;
					}
					else if(date.month == 12)
					{
						date.month = 1;
					}
					break;
				case STATE_YEAR:
					if(date.year < 99)
					{
						date.year++;
					}
					else if(date.year == 99)
					{
						date.year = 10;
					}
					break;
				case STATE_DAY:
					if(date.day < 7)
					{
						date.day++;
					}
					else if(date.day == 7)
					{
						date.day = 1;
					}
					break;
				default:
					break;
			}

			sprintf(display.line_2nd, "%d.%s.20%dr %s", date.date, rtc_month_roman[date.month - 1], date.year, rtc_day_str[date.day - 1]);
			lcd_clear_and_update(&display);
			HAL_Delay(100); // debouncing protection

		}

		if(button_read(BUTTON_DOWN) == BUTTON_PUSHED)
		{
			switch (current_substate) {
				case STATE_DATE:
					if(date.date > 1)
					{
						date.date--;
					}
					else if(date.date == 1)
					{
						date.date = 31;
					}
					break;
				case STATE_MONTH:
					if(date.month > 1)
					{
						date.month--;
					}
					else if(date.month == 1)
					{
						date.month = 12;
					}
					break;
				case STATE_YEAR:
					if(date.year > 10)
					{
						date.year--;
					}
					else if(date.year == 10)
					{
						date.year = 99;
					}
					break;
				case STATE_DAY:
					if(date.day > 1)
					{
						date.day--;
					}
					else if(date.day == 1)
					{
						date.day = 7;
					}
					break;
				default:
					break;
			}

			sprintf(display.line_2nd, "%d.%s.20%dr %s", date.date, rtc_month_roman[date.month - 1], date.year, rtc_day_str[date.day]);
			lcd_clear_and_update(&display);
			HAL_Delay(100); // debouncing protection
		}

		if(button_read(BUTTON_RIGHT) == BUTTON_PUSHED)
		{
			if(current_substate < 3)
			{
				current_substate++;
				HAL_Delay(200); // debouncing protection
			}
		}

		if(button_read(BUTTON_LEFT) == BUTTON_PUSHED)
		{
			if(current_substate > 0)
			{
				current_substate--;
				HAL_Delay(200); // debouncing protection
			}
		}

		if(button_read(BUTTON_ACCEPT) == BUTTON_PUSHED)
		{
			sprintf(display.line_1st, "    SET TIME    ");
			sprintf(display.line_2nd, "    %d:%d:%d    ", time.hours, time.minutes, time.seconds);


			lcd_clear_and_update(&display);

			HAL_Delay(200); // debouncing protection

			while(end_date_time_loop != true)
			{
				current_substate = STATE_HOURS;

				if(button_read(BUTTON_UP) == BUTTON_PUSHED)
				{
					if(current_substate == STATE_HOURS)
					{
						if(time.hours < 24)
						{
							time.hours++;
						}
					}
					else if(current_substate == STATE_MINUTES)
					{
						if(time.minutes < 59)
						{
							time.minutes++;
						}
					}
					else if(current_substate == STATE_SECONDS)
					{
						if(time.seconds < 59)
						{
							time.seconds++;
						}
					}

					switch (current_substate) {
						case STATE_HOURS:
							if(time.hours < 23)
							{
								time.hours++;
							}
							else if(time.hours == 23)
							{
								time.hours = 0;
							}
							break;
						case STATE_MINUTES:
							if(time.minutes < 59)
							{
								time.minutes++;
							}
							else if(time.minutes == 59)
							{
								time.minutes = 0;
							}
							break;
						case STATE_SECONDS:
							if(time.seconds < 59)
							{
								time.seconds++;
							}
							else if(time.seconds == 59)
							{
								time.seconds = 0;
							}
							break;
						default:
							break;
					}

					sprintf(display.line_2nd, "    %d:%d:%d", time.hours, time.minutes, time.seconds);
					lcd_update(&display, LINE_SECOND);
					HAL_Delay(100); // debouncing protection

				}

				if(button_read(BUTTON_DOWN) == BUTTON_PUSHED)
				{
					switch (current_substate) {
						case STATE_HOURS:
							if(time.hours > 1)
							{
								time.hours--;
							}
							else if(time.hours == 1)
							{
								time.hours = 23;
							}
							break;
						case STATE_MINUTES:
							if(time.minutes > 1)
							{
								time.minutes--;
							}
							else if(time.minutes == 1)
							{
								time.minutes = 59;
							}
							break;
						case STATE_SECONDS:
							if(time.seconds > 1)
							{
								time.seconds--;
							}
							else if(time.seconds == 1)
							{
								time.seconds = 59;
							}
							break;
						default:
							break;
					}
					sprintf(display.line_2nd, "    %d:%d:%d", time.hours, time.minutes, time.seconds);
					lcd_update(&display, LINE_SECOND);
					HAL_Delay(100); // debouncing protection

				}

				if(button_read(BUTTON_RIGHT) == BUTTON_PUSHED)
				{
					if(current_substate < 6)
					{
						current_substate++;
						HAL_Delay(100); // debouncing protection
					}
				}

				if(button_read(BUTTON_LEFT) == BUTTON_PUSHED)
				{
					if(current_substate > 4)
					{
						current_substate--;
						HAL_Delay(100); // debouncing protection
					}
				}

				if(button_read(BUTTON_ACCEPT) == BUTTON_PUSHED)
				{
					end_date_time_loop = true;

					rtc_set_time(&time);
					rtc_set_date(&date);
				}
			}
		}
	}
}

//void buzzer_service(void)
//{
//	buzzer_freq = BUZZER_250HZ;
//
//	buzzer_start();
//
//	uint32_t time = HAL_GetTick();
//
//	while(1)
//	{
//		if(HAL_GPIO_ReadPin(BUTTON_ACCEPT_PORT, BUTTON_ACCEPT_PIN) == GPIO_PIN_RESET)
//		{
//			break;
//		}
//		else if(time + 4000 <= HAL_GetTick())
//		{
//			buzzer_freq = BUZZER_250HZ;
//			time = HAL_GetTick();
//		}
//		else if(time + 3000 <= HAL_GetTick())
//		{
//			if(buzzer_melody == BUZZER_MELODY_3)
//			{
//				buzzer_freq = BUZZER_2000HZ;
//			}
//			else if(buzzer_melody == BUZZER_MELODY_2)
//			{
//				buzzer_freq = BUZZER_1000HZ;
//			}
//		}
//		else if(time + 2000 <= HAL_GetTick())
//		{
//			if(buzzer_melody == BUZZER_MELODY_3 || buzzer_melody == BUZZER_MELODY_1)
//			{
//				buzzer_freq = BUZZER_1000HZ;
//			}
//			else if(buzzer_melody == BUZZER_MELODY_2)
//			{
//				buzzer_freq = BUZZER_250HZ;
//			}
//		}
//		else if(time + 1000 <= HAL_GetTick())
//		{
//			if(buzzer_melody == BUZZER_MELODY_3)
//			{
//				buzzer_freq = BUZZER_500HZ;
//			}
//			else if(buzzer_melody == BUZZER_MELODY_2)
//			{
//				buzzer_freq = BUZZER_1000HZ;
//			}
//		}
//
//	}
//	buzzer_stop();
//}
