#include <LiquidCrystal_I2C.h>

// add this in platformio.ini
// lib_deps = marcoschwartz/LiquidCrystal_I2C@^1.1.4
// for ESP8266
// SDA -> D1
// SCL -> D2

LiquidCrystal_I2C lcd(0x27,16,2);  
// set the LCD address to 0x3F or 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Hello world!");
  
  lcd.setCursor(1,1);   //Move cursor to character 2 on line 1
  lcd.print("Budi Rahardjo");
}

void loop() {
}
