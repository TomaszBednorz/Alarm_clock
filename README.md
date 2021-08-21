# Alarm_clock

## Description
Small home project of alarm clock, which contains some easy to do features. Project is written in STM32CubeIDE, without CubeMX code generator. 

## Functionalities
- User can read current date and time from LCD display
- User can set two different alarms and current time by buttons
- Alarms trigger buzzer and LED
- User can choose different types of LED blinking and buzzer melody

## Bill of materials
- STM32F072RB Nucleo board
- DS3231 real time clock
- LCD display with HD44780 driver
- I2C converter to HD44780 (PCF8574)
- Buzzer
- Breadboard
- 5 x NO (normal open) buttons
- 5 x 100kOhms resistors
- Jumper wires

## TODO list
- [x] RTC library
- [x] LCD display library
- [x] Buzzer library
- [x] Clock functionality implementation
- [x] Alarms functionality implementation
- [x] Led && Buzzer functionality implementation
- [x] Comments actualization && bug revision

## Electrical diagram
![Alarm_clock_image](https://user-images.githubusercontent.com/62250785/129610810-a35a103d-5fc9-4486-b508-970c285dd7fa.PNG)

## Video
https://user-images.githubusercontent.com/62250785/129609163-3a5d4805-ee18-41be-baff-18f1760903d1.mp4


