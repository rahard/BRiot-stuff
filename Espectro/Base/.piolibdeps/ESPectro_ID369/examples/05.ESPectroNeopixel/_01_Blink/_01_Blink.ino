/*
  Blink on-board Neopixel RGB LED using ESPectro library
  Turns on-board Neopixel RGB LED on for one second, then off for one second, repeatedly.

  Created by 22 Sep 2016
  by Andri Yadi
*/

#include <ESPectro.h>

ESPectro board(ESPectro_V3);

// the setup function runs once when you press reset or power the board
void setup() {
    board.turnOffAllNeopixel();
}

// the loop function runs over and over again forever
void loop() {
    board.turnOnNeopixel(HtmlColor(0x0000ff));
    delay(1000);
    board.turnOffNeopixel();
    delay(1000);
}
