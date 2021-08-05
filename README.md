# Alarm_clock

## Description
Small home project of alarm clock, which contain some easy to do features. Project is written in STM32CubeIDE, without CubeMX code generator. 

## Functionality
- User can read current date and time from LCD display
- User can set two different alarms and current time by buttons
- Alarms trigger buzzer and LED strip
- User can choose different types of LED blinking and buzzer sounds

## Bill of materials
- STM32 Nucleo F072RB
- DS3231 real time clock
- LCD display with HD44780 driver
- I2C converter to HD44780 (PCF8574)
- Buzzer
- LED strip
- Breadboard
- Jumper wires

## TODO list
- [ ] RTC library
- [x] LCD display library
- [ ] LED strip  library
- [ ] Buzzer library
- [ ] Clock functionality implementation
- [ ] Alarms functionality implementation
