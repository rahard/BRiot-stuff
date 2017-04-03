#include <Adafruit_NeoPixel.h>

#define PIN            2
#define NUMPIXELS      3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 1000;
int i=0;
int j=0;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
    for (i=0; i<127; i=i+20) { 
       for (j=0; j<NUMPIXELS; j++) {
          pixels.setPixelColor(j, pixels.Color(63,i,0));
          pixels.show(); 
          delay(delayval);
       }
       for (j=0; j<NUMPIXELS; j++) {
          //pixels.setPixelColor(j, pixels.Color(63,30,0));
          pixels.setPixelColor(j, pixels.Color(63,0,0));
          pixels.show(); 
          delay(delayval);
       }
    }
}
