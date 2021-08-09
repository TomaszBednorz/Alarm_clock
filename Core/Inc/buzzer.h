#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

void buzzer_init(uint8_t melody);
void buzzer_start(void);
void buzzer_stop(void);

void buzzer_loop(void);

// User can set 3 buzzer melody. Param: @BUZZER_MELODY
#define BUZZER_MELODY_1		0
#define BUZZER_MELODY_2		1
#define BUZZER_MELODY_3		2

#define BUZZER_250HZ		2000
#define BUZZER_500HZ		1000
#define BUZZER_1000HZ		500
#define BUZZER_2000HZ		250
#define BUZZER_4000HZ		125

#endif /* INC_BUZZER_H_ */
