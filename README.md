# Alarm_clock

## Description
Small home project of alarm clock, which contain some easy to do features. Project is written in STM32CubeIDE, without CubeMX code generator. 

## Functionality
- User can read current date and time from LCD display
- User can set two different alarms and current time by buttons
- Alarms trigger buzzer and LED
- User can choose different types of LED blinking and buzzer melody

## Bill of materials
- STM32 Nucleo F072RB
- DS3231 real time clock
- LCD display with HD44780 driver
- I2C converter to HD44780 (PCF8574)
- Buzzer
- Breadboard
- 5 x NO (normal open) button
- 5 x 100kOhms resistor 
- Jumper wires



## TODO list
- [x] RTC library
- [x] LCD display library
- [x] Buzzer library
- [x] Clock functionality implementation
- [x] Alarms functionality implementation
- [x] Led && Buzzer functionality implementation
- [ ] Comments actualization && bug revision