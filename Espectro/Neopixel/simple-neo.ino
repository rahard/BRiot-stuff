#include <Adafruit_NeoPixel.h>

#define PIN            15
#define NUMPIXELS      1 

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 1000;
int i=0;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
    for (i=0; i<127; i=i+10) { 
    pixels.setPixelColor(0, pixels.Color(63,i,0));
    pixels.show(); 
    delay(delayval);
    pixels.setPixelColor(0, pixels.Color(63,30,0));
    pixels.show(); 
    delay(delayval);
    }
}
