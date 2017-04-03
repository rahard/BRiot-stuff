/*
  Let's do some neopixel animations

  Created by Andri Yadi, Sept 22, 2016
  
 */

#include <ESPectro_Neopixel.h>
#include <DCX_Neopixel_Animation.h>

ESPectro_Neopixel_Default neopixel(3);

RgbColor pulseColor(HtmlColor(0x7f0000));
DCX_Neopixel_CyclonAnimation cyclonAnimation(neopixel);

const byte duration = 10; //10 seconds
unsigned long startTime = 0;

// the setup function runs once when you press reset or power the board
void setup() {
    neopixel.Begin();
    neopixel.Show();

    cyclonAnimation.setAnimationDirection(true);
    cyclonAnimation.start();

    startTime = millis();
}

// the loop function runs over and over again forever
void loop() {

    //Must be called inside loop()
    cyclonAnimation.run();

    //Stop animation after [duration] seconds, just to show you how to stop animation, though.
    if (millis() - startTime > (duration * 1000)) {
        cyclonAnimation.end();
    }
}
