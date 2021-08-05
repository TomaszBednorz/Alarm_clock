#include "main.h"

uint8_t bcd_to_bin(uint8_t bcd_number)
{
	uint8_t unity = bcd_number & 0x0F;
	uint8_t dozens = (bcd_number >> 4) * 10;

	return dozens + unity;
}

uint8_t bin_to_bcd(uint8_t bin_number)
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

int main(void)
{
	RTC_time time_write = {0};
	RTC_time time_read = {0};

	lcd_display disp;

	char buffer1[17];
	char buffer2[17];

	disp.backlight = 1;
	time_write.hours = 5;
	time_write.minutes = 6;
	time_write.seconds = 7;

	HAL_Init();

	i2c1_init();
	i2c2_init();

	lcd_init(&disp);

//	uint8_t sec = 20;
//	uint8_t sec_read;
//
//	if(HAL_I2C_Mem_Write(&hi2c2, 0xD0, 0x02, 1, &sec, 1, 1000) != HAL_OK)
//	{
//		error_handler();
//	}
//
//	if(HAL_I2C_Mem_Read(&hi2c2, 0xD0, 0x02, 1, &sec_read, 1, 50) != HAL_OK)
//	{
//		error_handler();
//	}


//	uint8_t num1 = bin_to_bcd(7);
//	uint8_t num2 = bin_to_bcd(17);
//	uint8_t num3 = bin_to_bcd(45);

	rtc_set_time(&time_write);

	time_read = rtc_get_time();

	sprintf(buffer1, "%d:%d:%d", time_write.hours, time_write.minutes, time_write.seconds);
	sprintf(buffer2, "%d:%d:%d", time_read.hours, time_read.minutes, time_read.seconds);
	//sprintf(buffer, "%d:%d:%d", bcd_to_bin(num1), bcd_to_bin(num2), bcd_to_bin(num3));

	sprintf(disp.line_1st, buffer1);
	sprintf(disp.line_2nd, buffer2);



	lcd_update(&disp);

  while (1)
  {

  }

}

void error_handler(void)
{
  while (1)
  {
	  // Infinity loop
  }
}

