#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f0xx_hal.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "basic_functionalities.h"
#include "i2c.h"
#include "lcd.h"
#include "rtc.h"
#include "buzzer.h"
#include "gpio.h"
#include "led_strip.h"

// Parameter of time_date_actualization function param: @STRICT_ACTUALIZATION
#define STRICT_UPDATE_TRUE		true
#define STRICT_UPDATE_FALSE		false

// States in main_menu function
#define STATE_TIME		0
#define STATE_ALARM1	1
#define STATE_ALARM2	2
#define STATE_BUZZER	3
#define STATE_LED		4
#define STATE_EXIT		5

void time_date_actualization(bool strict_update);
void main_menu(void);

#endif /* __MAIN_H */
