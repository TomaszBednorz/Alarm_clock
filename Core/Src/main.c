#include "main.h"



int main(void)
{
	lcd_display disp;
	disp.addr = (0x27 << 1);
	disp.backlight = 1;

	sprintf(disp.line_1st, "12 VI  12:14:15");
	sprintf(disp.line_2nd, "<-   Alarm 1   -->");

	HAL_Init();

	i2c1_init();




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

