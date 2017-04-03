/*
  Button

  Turns on and off on board LED, when pressing on board pushbutton

  Created by Andri Yadi, Sept 22, 2016
  
 */

#include <ESPectro.h>

ESPectro board;
ESPectro_Button button;

void onButtonDown() {
  board.turnOnLED();
  Serial.println(F("Button is considered Pushed"));
}

void onButtonLongPressed() {
  Serial.println(F("Button is considered Long Pressed"));
}

void onButtonUp() {
  board.turnOffLED();
  Serial.println(F("Button is considered Released"));
}
  
void setup() {

  Serial.begin(115200);

  //Wait for Serial to be available
  while(!Serial);

  //Begin button, must be called before registering event handlers
  button.begin();

  //Register event handler for "button down" event
  button.onButtonDown(onButtonDown);

  //Or you can try this way...
//  button.onButtonDown([]() {
//      board.turnOnLED();
//      Serial.println(F("Button is considered Pushed"));
//  });

  //Register event handler for "button long press" event
  button.onLongPressed(onButtonLongPressed);
  
//  button.onLongPressed([]() {
//      Serial.println(F("Button is considered Long Pressed"));
//  });

  //Register event handler for "button up" event
  button.onButtonUp(onButtonUp);
  
//  button.onButtonUp([]() {
//      board.turnOffLED();
//      Serial.println(F("Button is considered Released"));
//  });
}

void loop() {

  //Must be called inside loop
  button.run();
}
