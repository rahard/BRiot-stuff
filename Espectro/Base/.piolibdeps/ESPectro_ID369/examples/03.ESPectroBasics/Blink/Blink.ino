/*
  Blink using ESPectro library
  Turns on an LED on for one second, then off for one second, repeatedly.

  Created by 22 Sep 2016
  by Andri Yadi
*/

#include <ESPectro.h>

ESPectro board;

// the setup function runs once when you press reset or power the board
void setup() {
  //Blink built-in/onboard LED with interval 2000 miliseconds
  board.blinkLED(2000);
}

// the loop function runs over and over again forever
void loop() {

}
