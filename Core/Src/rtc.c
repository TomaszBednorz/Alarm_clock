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
	rtc_write(DS3231_RTC_SECONDS, bin_to_bcd(time->seconds));
	rtc_write(DS3231_RTC_MINUTES, bin_to_bcd(time->minutes));

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

}


static void rtc_write(uint8_t reg, uint8_t data)
{
	if(HAL_I2C_Mem_Write(&DS3231_RTC_I2C_HANDLE, DS3231_RTC_I2C_ADDR, DS3231_RTC_SECONDS, 1, &data, 1, HAL_MAX_DELAY) != HAL_OK)
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
