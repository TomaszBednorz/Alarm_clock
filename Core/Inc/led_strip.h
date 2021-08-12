#ifndef INC_LED_STRIP_H_
#define INC_LED_STRIP_H_

#include "main.h"

void led_init(void);
void led_update_color(uint8_t led, uint8_t red, uint8_t green, uint8_t blue);
void led_send_color();


// Defines related with led strip communication
#define RESET_CODE_LEN		40  // 40 * 1.25 us = 50 us (reset code)
#define LED_RGB_COLOR_LEN	24  // 8 bits for red, green and blue color
#define LED_NUM				8

#define LINE_HIGH			50  // High state of line at the end of transmission
#define CODE_1_HIGH			28  // 28 / 50 = 56%, 0.56 * 1.25 us = 0.7 us (1 code high time)
#define CODE_0_HIGH			14  // 14 / 50 = 28%, 0.28 * 1.25 us = 0.35 us (0 code high time)
#define CODE_RESET_HIGH		0   // reset code high time

#define GREEN_COLOR_OFFSET  0   // Special sequence in RGB frame
#define RED_COLOR_OFFSET 	8   // Special sequence in RGB frame
#define BLUE_COLOR_OFFSET   16  // Special sequence in RGB frame

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim); // Fcn in msp.c

#endif /* INC_LED_STRIP_H_ */
