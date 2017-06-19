#include <Adafruit_NeoPixel.h>

#define PIN            2
#define NUMPIXELS       3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int i;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
   for (i=0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show(); 
   }
}
