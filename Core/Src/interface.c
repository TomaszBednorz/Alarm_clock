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

// Led  variables
uint8_t led_sequence = 1;


static uint32_t num_of_sequence = 0; // Led and buzzer helper variable

uint8_t current_state;
uint8_t current_substate;

static char* rtc_month_roman[12] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII" };
static char* rtc_day_str[7] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

/*
 * Static function prototypes
 */
static void set_date_time(void);
static void set_alarm(RTC_alarm alarm, uint8_t alarm_num);
static void set_buzzer(void);
static void set_led(void);
static void led_service();
static void buzzer_service(void);

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

	if(time.seconds == 0 || strict_update == true)
	{
		lcd_clear_and_update(&display);
	}
	else
	{
		lcd_update(&display, LINE_SECOND);
	}

}

/*
 * Main menu (heart of application)
 */
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
					set_alarm(alarm_1, DS3231_RTC_ALARM_1);
					break;
				case STATE_ALARM2:
					set_alarm(alarm_2, DS3231_RTC_ALARM_2);
					break;
				case STATE_BUZZER:
					set_buzzer();
					break;
				case STATE_LED:
					set_led();
					break;
				case STATE_EXIT:
					end_main_menu_loop = true;
					time_date_actualization(STRICT_UPDATE_TRUE);
					break;
				default:
					break;
			}
			if(current_state != STATE_EXIT)
			{
				sprintf(display.line_1st, "   MAIN  MENU   ");
				sprintf(display.line_2nd, menu_options[current_state]);
				lcd_clear_and_update(&display);
			}
			HAL_Delay(200); // debouncing protection
		}
	}
}

/*
 * Function which setting time and date in clock (available in main menu)
 */
static void set_date_time(void)
{
	date.date = 1;
	date.month = DS3231_RTC_JANUARY;
	date.year = 10;
	date.day = DS3231_RTC_MONDAY;

	time.hours = 0;
	time.minutes = 0;
	time.seconds = 0;

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

			sprintf(display.line_2nd, "%d.%s.20%dr %s", date.date, rtc_month_roman[date.month - 1], date.year, rtc_day_str[date.day - 1]);
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

			current_substate = STATE_HOURS;

			while(end_date_time_loop != true)
			{
				if(button_read(BUTTON_UP) == BUTTON_PUSHED)
				{
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
							if(time.hours > 0)
							{
								time.hours--;
							}
							else if(time.hours == 0)
							{
								time.hours = 23;
							}
							break;
						case STATE_MINUTES:
							if(time.minutes > 0)
							{
								time.minutes--;
							}
							else if(time.minutes == 0)
							{
								time.minutes = 59;
							}
							break;
						case STATE_SECONDS:
							if(time.seconds > 0)
							{
								time.seconds--;
							}
							else if(time.seconds == 0)
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
						HAL_Delay(200); // debouncing protection
					}
				}

				if(button_read(BUTTON_LEFT) == BUTTON_PUSHED)
				{
					if(current_substate > 4)
					{
						current_substate--;
						HAL_Delay(200); // debouncing protection
					}
				}

				if(button_read(BUTTON_ACCEPT) == BUTTON_PUSHED)
				{
					rtc_set_time(&time);
					rtc_set_date(&date);

					end_date_time_loop = true;
				}
			}
		}
	}
}


static void set_alarm(RTC_alarm alarm, uint8_t alarm_num)
{
	current_substate = ALARM_STATE_HOURS;
	bool end_alarm_loop = false;

	alarm.minutes = 0;
	alarm.hours = 0;
	alarm.day = DS3231_RTC_MONDAY;

	if(alarm_num == DS3231_RTC_ALARM_1)
	{
		sprintf(display.line_1st, "   SET ALARM1   ");
	}else if(alarm_num == DS3231_RTC_ALARM_2)
	{
		sprintf(display.line_1st, "   SET ALARM2   ");
	}

	sprintf(display.line_2nd, "   %d:%d %s", alarm.hours, alarm.minutes, rtc_day_str[alarm.day - 1]);
	lcd_clear_and_update(&display);
	HAL_Delay(200); // debouncing protection

	while(end_alarm_loop != true)
	{
		if(button_read(BUTTON_UP) == BUTTON_PUSHED)
		{
			switch (current_substate) {
				case ALARM_STATE_HOURS:
					if(alarm.hours < 23)
					{
						alarm.hours++;
					}
					else if(alarm.hours == 23)
					{
						alarm.hours = 0;
					}
					break;
				case ALARM_STATE_MINUTES:
					if(alarm.minutes < 59)
					{
						alarm.minutes++;
					}
					else if(alarm.minutes == 59)
					{
						alarm.minutes = 0;
					}
					break;
				case ALARM_STATE_DAY:
					if(alarm.day < 7)
					{
						alarm.day++;
					}
					else if(alarm.day == 7)
					{
						alarm.day = 1;
					}
					break;
				default:
					break;

			}
			sprintf(display.line_2nd, "   %d:%d %s", alarm.hours, alarm.minutes, rtc_day_str[alarm.day - 1]);
			lcd_clear_and_update(&display);
			HAL_Delay(100); // debouncing protection
		}

		if(button_read(BUTTON_DOWN) == BUTTON_PUSHED)
		{
			switch (current_substate) {
				case ALARM_STATE_HOURS:
					if(alarm.hours > 0)
					{
						alarm.hours--;
					}
					else if(alarm.hours == 0)
					{
						alarm.hours = 23;
					}
					break;
				case ALARM_STATE_MINUTES:
					if(alarm.minutes > 0)
					{
						alarm.minutes--;
					}
					else if(alarm.minutes == 0)
					{
						alarm.minutes = 23;
					}
					break;
				case ALARM_STATE_DAY:
					if(alarm.day > 1)
					{
						alarm.day--;
					}
					else if(alarm.day == 1)
					{
						alarm.day = 7;
					}
					break;
				default:
					break;
			}
			sprintf(display.line_2nd, "   %d:%d %s", alarm.hours, alarm.minutes, rtc_day_str[alarm.day - 1]);
			lcd_clear_and_update(&display);
			HAL_Delay(100); // debouncing protection
		}

		if(button_read(BUTTON_RIGHT) == BUTTON_PUSHED)
		{
			if(current_substate < 2)
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
			rtc_set_alarm(&alarm, alarm_num);
			end_alarm_loop = true;
		}

	}
}

static void set_buzzer(void)
{
	bool end_buzzer_loop = false;

	buzzer_melody = BUZZER_MELODY_1;


	sprintf(display.line_1st, "   SET BUZZER   ");
	sprintf(display.line_2nd, "<-BUZ MELODY %d->", buzzer_melody);
	lcd_clear_and_update(&display);
	HAL_Delay(200); // debouncing protection

	while(end_buzzer_loop != true)
	{
		if(button_read(BUTTON_RIGHT) == BUTTON_PUSHED)
		{
			if(buzzer_melody < 2)
			{
				buzzer_melody++;
				sprintf(display.line_2nd, "<-BUZ MELODY %d->", buzzer_melody);
				lcd_update(&display, LINE_SECOND);
				HAL_Delay(100); // debouncing protection
			}
		}

		if(button_read(BUTTON_LEFT) == BUTTON_PUSHED)
		{
			if(buzzer_melody > 1)
			{
				buzzer_melody--;
				sprintf(display.line_2nd, "<-BUZ MELODY %d->", buzzer_melody);
				lcd_update(&display, LINE_SECOND);
				HAL_Delay(100); // debouncing protection
			}
		}

		if(button_read(BUTTON_ACCEPT) == BUTTON_PUSHED)
		{
			end_buzzer_loop = true;
		}
	}
}

static void set_led(void)
{
	bool end_led_loop = false;

	led_sequence = 1;


	sprintf(display.line_1st, "SET LED SEQUENCE");
	sprintf(display.line_2nd, "<- LED SEQ %d ->", led_sequence);
	lcd_clear_and_update(&display);
	HAL_Delay(200); // debouncing protection

	while(end_led_loop != true)
	{
		if(button_read(BUTTON_RIGHT) == BUTTON_PUSHED)
		{
			if(led_sequence < 2)
			{
				led_sequence++;
				sprintf(display.line_2nd, "<- LED SEQ %d ->", led_sequence);
				lcd_update(&display, LINE_SECOND);
				HAL_Delay(100); // debouncing protection
			}
		}

		if(button_read(BUTTON_LEFT) == BUTTON_PUSHED)
		{
			if(led_sequence > 1)
			{
				led_sequence--;
				sprintf(display.line_2nd, "<- LED SEQ %d ->", led_sequence);
				lcd_update(&display, LINE_SECOND);
				HAL_Delay(100); // debouncing protection
			}
		}

		if(button_read(BUTTON_ACCEPT) == BUTTON_PUSHED)
		{
			end_led_loop = true;
		}
	}
}


void alarm_service(void)
{
	bool end_alarm_service_loop = false;
	uint8_t active_alarms = is_alarm_activeted();

	if(active_alarms)
	{
		if(active_alarms == DS3231_RTC_ALARM_1)
		{
			sprintf(display.line_1st, "    ALARM  1");
		}
		else if(active_alarms == DS3231_RTC_ALARM_2)
		{
			sprintf(display.line_1st, "    ALARM  2");
		}

		sprintf(display.line_2nd, "CLICK BUTTON !!!");
		lcd_clear_and_update(&display);


		uint32_t time = HAL_GetTick();

		buzzer_service();
		led_service();
		buzzer_start();


		while(end_alarm_service_loop != true)
		{

			if(time + 500 <= HAL_GetTick())
			{
				time = HAL_GetTick();

				num_of_sequence++;
				buzzer_service();
				led_service();

			}

			if(button_read(BUTTON_ACCEPT) == BUTTON_PUSHED)
			{
				buzzer_stop();
				HAL_GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, GPIO_PIN_RESET);
				end_alarm_service_loop = true;

				if(active_alarms == DS3231_RTC_ALARM_1)
				{
					rtc_alarm_disable(DS3231_RTC_ALARM_1);
				}
				else if(active_alarms == DS3231_RTC_ALARM_2)
				{
					rtc_alarm_disable(DS3231_RTC_ALARM_2);
				}

				time_date_actualization(STRICT_UPDATE_TRUE);

			}
		}
	}
}

static void led_service()
{
	if(num_of_sequence % 2 == 0 && led_sequence == 1)
	{
		HAL_GPIO_TogglePin(RED_LED_PORT, RED_LED_PIN);
	}
	else if(led_sequence == 2)
	{
		HAL_GPIO_TogglePin(RED_LED_PORT, RED_LED_PIN);
	}
}



static void buzzer_service(void)
{
	if(num_of_sequence % 2 == 0 && buzzer_melody == 1)
	{
		buzzer_freq = BUZZER_250HZ;
	}
	else if(num_of_sequence % 2 == 1 && buzzer_melody == 1)
	{
		buzzer_freq = BUZZER_500HZ;
	}

	if(num_of_sequence % 3 == 0 && buzzer_melody == 2)
	{
		buzzer_freq = BUZZER_250HZ;
	}
	else if(num_of_sequence % 3 == 1 && buzzer_melody == 2)
	{
		buzzer_freq = BUZZER_500HZ;
	}
	else if(num_of_sequence % 3 == 2 && buzzer_melody == 2)
	{
		buzzer_freq = BUZZER_1000HZ;
	}


}
