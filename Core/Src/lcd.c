#include "lcd.h"

static void lcd_write(uint8_t data, uint8_t add_pins)
{
	uint8_t tx_data[4];

	tx_data[0] = (data & 0xF0) | EN_PIN | add_pins;
	tx_data[1] = (data & 0xF0) | add_pins;
	tx_data[2] = (data << 4) | EN_PIN | add_pins;
	tx_data[3] = (data << 4) | add_pins;

	if(HAL_I2C_Master_Transmit(&LCD_I2C_HANDLE, LCD_I2C_ADDR, tx_data, 4, 50))
	{
		error_handler();
	}
	HAL_Delay(5);
}

/*
 * LCD initialization in 4 bit mode
 */
void lcd_init(lcd_display* lcd)
{
	uint8_t bl = 0;
	if(lcd->backlight)
	{
		bl = BL_PIN;
	}

	// LCD initialization
	HAL_Delay(40);
	lcd_write(CMD_8_BIT_INIT, bl);
	HAL_Delay(5);
	lcd_write(CMD_8_BIT_INIT, bl);
	HAL_Delay(1);
	lcd_write(CMD_8_BIT_INIT, bl);

	lcd_write(CMD_4_BIT_INIT, bl);
	lcd_write(CURSOR_OFF_BLINKING_OFF, bl);
	lcd_write(CMD_LCD_CLEAR, bl);
}

/*
 * Function which clears LCD display
 */
void lcd_clear(lcd_display* lcd)
{
	uint8_t bl = 0;
	if(lcd->backlight)
	{
		bl = BL_PIN;
	}

	lcd_write(CMD_LCD_CLEAR, bl);
}

/*
 * Function which sends information contained in lcd_display struct to lcd display
 */
void lcd_update(lcd_display* lcd)
{
	uint8_t bl = 0;
	if(lcd->backlight)
	{
		bl = BL_PIN;
	}

	lcd_clear(lcd);

	lcd_write(FIRST_LINE, bl);
	for(int i = 0; i < fmin(strlen(lcd->line_1st), LINE_LEN); i++)
	{
		lcd_write(lcd->line_1st[i] , (bl | RS_PIN));
	}

	lcd_write(SECOND_LINE, bl);
	for(int i = 0; i < fmin(strlen(lcd->line_2nd), LINE_LEN); i++)
	{
		lcd_write(lcd->line_2nd[i] , (bl | RS_PIN));
	}
}
