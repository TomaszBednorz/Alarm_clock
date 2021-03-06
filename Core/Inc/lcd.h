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

/* Configurable items */
#define LCD_I2C_HANDLE 	hi2c1
#define LCD_I2C_ADDR 	(0x27 << 1)

// Pins in LCD
#define RS_PIN			0x1
#define RW_PIN			0x2
#define EN_PIN			0x4
#define BL_PIN			0x8

// Addresses of lines in LCD
#define FIRST_LINE		0x80
#define SECOND_LINE		0xC0

// Commands
#define CMD_8_BIT_INIT	0x30
#define CMD_4_BIT_INIT 	0x02
#define CMD_LCD_CLEAR  	0x01

// Cursor configuration
#define CURSOR_OFF_BLINKING_OFF		0x0C
#define CURSOR_OFF_BLINKING_ON		0x0D
#define CURSOR_ON_BLINKING_OFF		0x0E
#define CURSOR_ON_BLINKING_ON		0x0F

#define LINE_LEN	16

// Which line to update param: @LCD_UPDATE
#define LINE_BOTH		(LINE_FIRST | LINE_SECOND)
#define LINE_FIRST		1
#define LINE_SECOND		2

// LCD struct
typedef struct
{
	bool backlight;
	char line_1st[17];
	char line_2nd[17];
}lcd_display;


void lcd_init(lcd_display* lcd);
void lcd_clear(lcd_display* lcd);
void lcd_clear_and_update(lcd_display* lcd);
void lcd_update(lcd_display* lcd, uint8_t line);




#endif /* INC_LCD_H_ */
