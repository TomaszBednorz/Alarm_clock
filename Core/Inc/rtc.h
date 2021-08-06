#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

extern I2C_HandleTypeDef hi2c2;

/* Configurable items */
#define DS3231_RTC_I2C_HANDLE 	hi2c2
#define DS3231_RTC_I2C_ADDR 	0xD0

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
#define DS3231_STATUS			0x0F
#define DS3231_OFFSET			0x10
#define DS3231_MSP_TEMP			0x11
#define DS3231_LSB_TEMP			0x12

// RTC contains 2 different alarms. Param: @RTC_DS3231_ALARM
#define DS3231_RTC_ALARM_1		1
#define DS3231_RTC_ALARM_2		2

// Define for RTC alarm enable or disable. Param: @RTC_DS3231_CONTROL
#define DS3231_RTC_AL_ENABLE	1
#define DS3231_RTC_AL_DISABLE	0

// param @RTC_DS3231_DAY
#define DS3231_RTC_SUNDAY 		1
#define DS3231_RTC_MONDAY		2
#define DS3231_RTC_TUESDAY		3
#define DS3231_RTC_WEDNESDAY	4
#define DS3231_RTC_THURSDAY		5
#define DS3231_RTC_FRIDAY		6
#define DS3231_RTC_SATURDAY		7

// param @RTC_DS3231_Month
#define DS3231_RTC_JANUARY 		1
#define DS3231_RTC_FEBRUARY		2
#define DS3231_RTC_MARCH		3
#define DS3231_RTC_APRIL		4
#define DS3231_RTC_MAY			5
#define DS3231_RTC_JUNE			6
#define DS3231_RTC_JULY			7
#define DS3231_RTC_AUGUST		8
#define DS3231_RTC_SEPTEMBER	9
#define DS3231_RTC_OCTOBER		10
#define DS3231_RTC_NOVEMBER		11
#define DS3231_RTC_DECEMBER		12

// Hours format in DS3231_RTC_HOURS / DS3231_AL1_HOURS / DS3231_AL2_HOURS registers
#define DS3231_RTC_24_HOURS_FORMAT		(0 << 6)
#define DS3231_RTC_12_HOURS_FORMAT		(1 << 6)

// Day/date format in DS3231_AL1_HOURS / DS3231_AL2_HOURS registers
#define DS3231_RTC_DAY_FORMAT		(1 << 6)
#define DS3231_RTC_DATE_FORMAT		(0 << 6)

// Century in DS3231_RTC_MONTH_CTR register
#define DS3231_RTC_21_CENTURY		(0 << 7)
#define DS3231_RTC_22_CENTURY		(1 << 7)

// DS3231 register masks (for value to read and write)
#define DS3231_RTC_SECONDS_MASK		0x7F
#define DS3231_RTC_MINUTES_MASK		0x7F
#define DS3231_RTC_HOURS_MASK		0x3F
#define DS3231_RTC_DAY_MASK			0x07
#define DS3231_RTC_DATE_MASK		0x3F
#define DS3231_RTC_MONTH_MASK		0x1F

/*
 * Bitmasks
 */
#define DS3231_RTC_CTRL_A1IE  		0x01 	// Bitmask's in DS3231_CTRL
#define DS3231_RTC_CTRL_A2IE 		0x02
#define DS3231_RTC_CTRL_INTCN		0x04
#define DS3231_RTC_CTRL_RS1			0x08
#define DS3231_RTC_CTRL_RS2			0x10
#define DS3231_RTC_CTRL_CONV		0x20
#define DS3231_RTC_CTRL_BBSQW		0x40
#define DS3231_RTC_CTRL_EOSC		0x80

#define DS3231_RTC_STATUS_A1F	  	0x01 	// Bitmask's in DS3231_STATUS
#define DS3231_RTC_STATUS_A2F		0x02
#define DS3231_RTC_STATUS_BSY		0x04
#define DS3231_RTC_STATUS_EN32KHZ	0x08
#define DS3231_RTC_STATUS_OSF		0x80

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
void rtc_set_time(RTC_time *time);
RTC_time rtc_get_time(void);
void rtc_set_date(RTC_date *date);
RTC_date rtc_get_date(void);
void rtc_set_alarm(RTC_alarm *alarm, uint8_t alarm_num);
RTC_alarm rtc_get_alarm(uint8_t alarm_num);
void rtc_alarm_disable(uint8_t alarm_num);
uint8_t is_alarm_activeted(void);


#endif /* INC_RTC_H_ */
