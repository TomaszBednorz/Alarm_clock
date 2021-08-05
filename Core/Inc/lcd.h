/* Library for LCD display with HD44780 driver. In this implementation I2C converter is used (PCF8574). */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"

extern I2C_HandleTypeDef hi2c1;

/*
 * PCF8574 ---> HD44780
 *
 * I2C:  P7 P6 P5 P4 P3 P2 P1 P0
 * LCD:  D7 D6 D5 D4 BL EN RW RS
 *
 */

#define I2C_HANDLE hi2c1

#define RS_PIN			0x1
#define RW_PIN			0x2
#define EN_PIN			0x4
#define BL_PIN			0x8

#define FIRST_LINE		0x80
#define SECOND_LINE		0xC0

#define CMD_8_BIT_INIT	0x30
#define CMD_4_BIT_INIT 	0x02
#define CMD_LCD_CLEAR  	0x01

#define CURSOR_OFF_BLINKING_OFF		0x0C
#define CURSOR_OFF_BLINKING_ON		0x0D
#define CURSOR_ON_BLINKING_OFF		0x0E
#define CURSOR_ON_BLINKING_ON		0x0F

#define LINE_LEN	16

typedef struct
{
	uint8_t addr;
	bool backlight;
	char line_1st[17];
	char line_2nd[17];
}lcd_display;

void lcd_init(lcd_display* lcd);
void lcd_clear(lcd_display* lcd);
void lcd_update(lcd_display* lcd);




#endif /* INC_LCD_H_ */
