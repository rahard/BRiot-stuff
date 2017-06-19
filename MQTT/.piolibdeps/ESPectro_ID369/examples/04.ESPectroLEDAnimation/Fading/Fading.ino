/*
  Fading built-in LED using ESPectro library
  
  Created by 17 Mar 2017
  by Andri Yadi
*/

#include <ESPectro.h>

ESPectro board;

// the setup function runs once when you press reset or power the board
void setup() {

  //Just in case RGB neopixel is light up, turn all off
  board.turnOffAllNeopixel();

  //Fading built-in/onboard LED with interval 1000 miliseconds, for 10 times
  board.getLED().fade(1000, 10);
}

// the loop function runs over and over again forever
void loop() {
  //Nothing here. Yay!
}
