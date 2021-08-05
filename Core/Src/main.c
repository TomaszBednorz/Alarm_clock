#include "main.h"



int main(void)
{
	lcd_display disp;
	disp.addr = (0x27 << 1);
	disp.backlight = 1;

	sprintf(disp.line_1st, "12 VI 21r MON");
	sprintf(disp.line_2nd, "10:11:12 AM 27*C");

	HAL_Init();

	i2c1_init();
	i2c2_init();



	lcd_init(&disp);

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

