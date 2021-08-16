#ifndef INC_INTERFACE_H_
#define INC_INTERFACE_H_

#include "main.h"

// Parameter of time_date_actualization function param: @STRICT_ACTUALIZATION
#define STRICT_UPDATE_TRUE		true
#define STRICT_UPDATE_FALSE		false

// States in main_menu function
#define STATE_DATE_TIME 0
#define STATE_ALARM1	1
#define STATE_ALARM2	2
#define STATE_BUZZER	3
#define STATE_LED		4
#define STATE_EXIT		5

// Sub states in main_menu sub function (set_date_time, set_alarm). Param: @CURRENT_STATE
#define STATE_DATE		0
#define STATE_MONTH		1
#define STATE_YEAR		2
#define STATE_DAY		3
#define STATE_HOURS		4
#define STATE_MINUTES	5
#define STATE_SECONDS	6

// Sub states in main_menu sub function (set_alarm). Param: @CURRENT_SUBSTATE
#define ALARM_STATE_HOURS		0
#define ALARM_STATE_MINUTES		1
#define ALARM_STATE_DAY			2

void time_date_actualization(bool strict_update);
void main_menu(void);
void alarm_service(void);


#endif /* INC_INTERFACE_H_ */
