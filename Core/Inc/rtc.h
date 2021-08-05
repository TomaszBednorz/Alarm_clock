#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

/* Configurable items */
#define RTC_I2C_HANDLE 	hi2c2

/*
 * DS3231 registers
 */
#define DS3231_RTC_SECONDS		0x00  // RTC registers
#define DS3231_RTC_MINUTES		0x01
#define DS3231_RTC_HOURS		0x02
#define DS3231_RTC_DAY			0x03
#define DS3231_RTC_DATE			0x04
#define DS3231_RTC_MONTH_CTR	0x05
#define DS3231_RTC_YEAR			0x06
#define DS3231_AL1_SECONDS		0x07  // Alarm 1 registers
#define DS3231_AL1_MINUTES		0x08
#define DS3231_AL1_HOURS		0x09
#define DS3231_AL1_DAY_DATE		0x0A  // Alarm 2 registers
#define DS3231_AL2_MINUTES		0x0B
#define DS3231_AL2_HOURS		0x0C
#define DS3231_AL2_DAY_DATE		0x0D
#define DS3231_CTRL				0x0E  // Other registers
#define DS3231_CTRL_STATUS		0x0F
#define DS3231_OFFSET			0x10
#define DS3231_MSP_TEMP			0x11
#define DS3231_LSB_TEMP			0x12

// RTC contains 2 different alarms. Param: @RTC_DS3231_ALARM
#define ALARM_1					1
#define ALARM_2					2

// param @RTC_DS3231_DAY
#define RTC_SUNDAY 		1
#define RTC_MONDAY		2
#define RTC_TUESDAY		3
#define RTC_WEDNESDAY	4
#define RTC_THURSDAY	5
#define RTC_FRIDAY		6
#define RTC_SATURDAY	7

// param @RTC_DS3231_Month
#define RTC_JANUARY 	1
#define RTC_FEBRUARY	2
#define RTC_MARCH		3
#define RTC_APRIL		4
#define RTC_MAY			5
#define RTC_JUNE		6
#define RTC_JULY		7
#define RTC_AUGUST		8
#define RTC_SEPTEMBER	9
#define RTC_OCTOBER		10
#define RTC_NOVEMBER	11
#define RTC_DECEMBER	12

/*
 * Structures
 */
typedef struct
{
	uint8_t seconds;  	// 0 - 59
	uint8_t minutes; 	// 0 - 59
	uint8_t hours;    	// 0 - 23
}RTC_time;

typedef struct
{
	uint8_t day;		// param: @RTC_DS3231_DAY
	uint8_t date;		// 1 - 31
	uint8_t month;		// @RTC_DS3231_Month
	uint8_t year;		// 0 - 99 (+2000)
}RTC_date;

typedef struct
{
	uint8_t minutes;    // 0 - 59
	uint8_t hours;      // 0 - 59
	uint8_t day;		// param: @RTC_DS3231_DAY
}RTC_alarm;

/*
 * Functions prototypes
 */

void rtc_init(void);
void rtc_set_time(RTC_time *time);
RTC_time rtc_get_time(void);
void rtc_set_date(RTC_date *date);
RTC_date rtc_get_date(void);
void rtc_set_alarm(RTC_alarm *alarm, uint8_t alarm_num);
RTC_alarm rtc_get_alarm(uint8_t alarm_num);



#endif /* INC_RTC_H_ */
