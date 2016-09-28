/*
  Blink on-board Neopixel RGB LED using ESPectro library
  Turns on-board Neopixel RGB LED on for one second, then off for one second, repeatedly.

  Created by 22 Sep 2016
  by Andri Yadi
*/

#include <ESPectro_Neopixel.h>

ESPectro_Neopixel_Default neopixel;

// the setup function runs once when you press reset or power the board
void setup() {
  neopixel.Begin();
  neopixel.Show();
}

// the loop function runs over and over again forever
void loop() {
  neopixel.turnOn(HtmlColor(0x0000ff));
  delay(1000);
  neopixel.turnOff();
  delay(1000);
}
