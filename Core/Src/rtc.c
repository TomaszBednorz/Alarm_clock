#include "rtc.h"

/*
 * Static function prototypes
 */
static void rtc_write(uint8_t reg, uint8_t data);
static uint8_t rtc_read(uint8_t reg);
static uint8_t bcd_to_bin(uint8_t bcd_number);
static uint8_t bin_to_bcd(uint8_t bin_number);

/*
 * @fn      		  - rtc_set_time
 *
 * @param[in]         - RTC_time structure
 *
 * @return            - None
 *
 * @Note              - This function set time in the DS3231 RTC
 */
void rtc_set_time(RTC_time *time)
{
	rtc_write(DS3231_RTC_SECONDS, bin_to_bcd(time->seconds) & DS3231_RTC_SECONDS_MASK);

	rtc_write(DS3231_RTC_MINUTES, bin_to_bcd(time->minutes) & DS3231_RTC_MINUTES_MASK);

	uint8_t hours = DS3231_RTC_24_HOURS_FORMAT | ( bin_to_bcd(time->hours) & DS3231_RTC_HOURS_MASK );
	rtc_write(DS3231_RTC_HOURS, hours);
}

/*
 * @fn      		  - rtc_get_time
 *
 * @return            - RTC_time structure
 *
 * @Note              - This function return time from the DS3231 RTC
 */
RTC_time rtc_get_time(void)
{
	RTC_time time;

	time.seconds = bcd_to_bin(rtc_read(DS3231_RTC_SECONDS) & DS3231_RTC_SECONDS_MASK);
	time.minutes = bcd_to_bin(rtc_read(DS3231_RTC_MINUTES) & DS3231_RTC_MINUTES_MASK);
	time.hours = bcd_to_bin(rtc_read(DS3231_RTC_HOURS) & DS3231_RTC_HOURS_MASK);

	return time;
}

/*
 * @fn      		  - rtc_set_date
 *
 * @param[in]         - RTC_date structure
 *
 * @return            - None
 *
 * @Note              - This function set date in the DS3231 RTC
 */
void rtc_set_date(RTC_date *date)
{
	rtc_write(DS3231_RTC_DAY, bin_to_bcd(date->day) & DS3231_RTC_DAY_MASK);

	rtc_write(DS3231_RTC_DATE, bin_to_bcd(date->date) & DS3231_RTC_DATE_MASK);

	uint8_t months = DS3231_RTC_21_CENTURY | ( bin_to_bcd(date->month) & DS3231_RTC_MONTH_MASK );
	rtc_write(DS3231_RTC_MONTH_CTR, months);

	rtc_write(DS3231_RTC_YEAR, bin_to_bcd(date->year));
}

/*
 * @fn      		  - rtc_set_date
 *
 * @return            - RTC_date structure
 *
 * @Note              - This function return date from the DS3231 RTC
 */
RTC_date rtc_get_date(void)
{
	RTC_date date;

	date.day = bcd_to_bin(rtc_read(DS3231_RTC_DAY) & DS3231_RTC_DAY_MASK);
	date.date = bcd_to_bin(rtc_read(DS3231_RTC_DATE) & DS3231_RTC_DATE_MASK);
	date.month = bcd_to_bin(rtc_read(DS3231_RTC_MONTH_CTR) & DS3231_RTC_MONTH_MASK);
	date.year = bcd_to_bin(rtc_read(DS3231_RTC_YEAR));

	return date;
}

/*
 * @fn      		  - rtc_set_date
 *
 * @param[in]         - RTC_alarm structure
 * @param[in]         - alarm_num - param: @RTC_DS3231_ALARM
 *
 * @return            - None
 *
 * @Note              - This function set alarm in the DS3231 RTC
 */
void rtc_set_alarm(RTC_alarm *alarm, uint8_t alarm_num)
{
	if(alarm_num == DS3231_RTC_ALARM_1)
	{
		rtc_write(DS3231_AL1_MINUTES, bin_to_bcd(alarm->minutes) & DS3231_RTC_MINUTES_MASK);

		uint8_t hours = DS3231_RTC_24_HOURS_FORMAT | ( bin_to_bcd(alarm->hours) & DS3231_RTC_HOURS_MASK );
		rtc_write(DS3231_AL1_HOURS, hours);

		uint8_t day = DS3231_RTC_DAY_FORMAT | ( bin_to_bcd(alarm->day) & DS3231_RTC_DAY_MASK );
		rtc_write(DS3231_AL1_DAY_DATE, day);
	}
	else if(alarm_num == DS3231_RTC_ALARM_2)
	{
		rtc_write(DS3231_AL2_MINUTES, bin_to_bcd(alarm->minutes) & DS3231_RTC_MINUTES_MASK);

		uint8_t hours = DS3231_RTC_24_HOURS_FORMAT | ( bin_to_bcd(alarm->hours) & DS3231_RTC_HOURS_MASK );
		rtc_write(DS3231_AL2_HOURS, hours);

		uint8_t day = DS3231_RTC_DAY_FORMAT | ( bin_to_bcd(alarm->day) & DS3231_RTC_DAY_MASK );
		rtc_write(DS3231_AL2_DAY_DATE, day);
	}
}

/*
 * @fn      		  - rtc_get_alarm
 *
 * @param[in]         - alarm_num - param: @RTC_DS3231_ALARM
 *
 * @return            - RTC_alarm structure
 *
 * @Note              - This function return alarm time from the DS3231 RTC
 */
RTC_alarm rtc_get_alarm(uint8_t alarm_num)
{
	RTC_alarm alarm;

	if(alarm_num == DS3231_RTC_ALARM_1)
	{
		alarm.minutes = bcd_to_bin(rtc_read(DS3231_AL1_MINUTES) & DS3231_RTC_MINUTES_MASK);
		alarm.hours = bcd_to_bin(rtc_read(DS3231_AL1_HOURS) & DS3231_RTC_HOURS_MASK);
		alarm.day = bcd_to_bin(rtc_read(DS3231_AL1_DAY_DATE) & DS3231_RTC_DAY_MASK);
	}
	else if(alarm_num == DS3231_RTC_ALARM_2)
	{
		alarm.minutes = bcd_to_bin(rtc_read(DS3231_AL2_MINUTES) & DS3231_RTC_MINUTES_MASK);
		alarm.hours = bcd_to_bin(rtc_read(DS3231_AL2_HOURS) & DS3231_RTC_HOURS_MASK);
		alarm.day = bcd_to_bin(rtc_read(DS3231_AL2_DAY_DATE) & DS3231_RTC_DAY_MASK);
	}

	return alarm;
}

/*
 * @fn      		  - rtc_alarm_disable
 *
 * @param[in]         - alarm_num - param: @RTC_DS3231_ALARM
 *
 * @return            - None
 *
 * @Note              - This function disable alarm in DS3231 RTC
 */
void rtc_alarm_disable(uint8_t alarm_num)
{
	uint8_t status_reg = 0;

	// Default options in DS3231_STATUS register
	status_reg |= DS3231_RTC_STATUS_A1F;
	status_reg |= DS3231_RTC_STATUS_A2F;
	status_reg |= DS3231_RTC_STATUS_EN32KHZ;
	status_reg |= DS3231_RTC_STATUS_OSF;

	if(alarm_num & DS3231_RTC_ALARM_1)
	{
		status_reg &= ~(DS3231_RTC_CTRL_A1IE);
	}

	if(alarm_num & DS3231_RTC_ALARM_2)
	{
		status_reg &= ~(DS3231_RTC_CTRL_A2IE);
	}



	rtc_write(DS3231_STATUS, status_reg);
}

/*
 * @fn      		  - is_alarm_activeted
 *
 * @return            - param: @RTC_DS3231_ALARM
 *
 * @Note              - This function return:
 * 						0 - neither alarms are activated
 * 						1 - DS3231_RTC_ALARM_1 activated
 * 						2 - DS3231_RTC_ALARM_2 activated
 * 						3 - either alarms are activated
 */
uint8_t is_alarm_activeted(void)
{
	uint8_t status_reg = 0;
	uint8_t activ_alarms = 0;
	status_reg = rtc_read(DS3231_STATUS);

	if(status_reg & DS3231_RTC_STATUS_A1F)
	{
		activ_alarms |= DS3231_RTC_ALARM_1;
	}

	if(status_reg & DS3231_RTC_STATUS_A2F)
	{
		activ_alarms |= DS3231_RTC_ALARM_2;
	}

	return activ_alarms;
}




static void rtc_write(uint8_t reg, uint8_t data)
{
	if(HAL_I2C_Mem_Write(&DS3231_RTC_I2C_HANDLE, DS3231_RTC_I2C_ADDR, reg, 1, &data, 1, HAL_MAX_DELAY) != HAL_OK)
	{
		error_handler();
	}
}


static uint8_t rtc_read(uint8_t reg)
{
	uint8_t rx_data;

	if(HAL_I2C_Mem_Read(&DS3231_RTC_I2C_HANDLE, DS3231_RTC_I2C_ADDR, reg, 1, &rx_data, 1, 50) != HAL_OK)
	{
		error_handler();
	}

	return rx_data;
}

static uint8_t bcd_to_bin(uint8_t bcd_number)
{
	uint8_t unity = bcd_number & 0x0F;
	uint8_t dozens = (bcd_number >> 4) * 10;

	return dozens + unity;
}

static uint8_t bin_to_bcd(uint8_t bin_number)
{
	uint8_t unity = 0;
	uint8_t dozens = 0;
	uint8_t bcd_number = bin_number;

	if(bcd_number >= 10)
	{
		unity = bin_number % 10;
		dozens = bin_number / 10;
		bcd_number = unity | (dozens << 4);
	}
	return bcd_number;
}
