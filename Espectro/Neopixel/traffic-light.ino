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

    // red
    pixels.setPixelColor(0, pixels.Color(63,0,0));
    pixels.show(); 
    delay(3000);

    for (i=0; i<5; i++) {
      // yellow
      pixels.setPixelColor(0, pixels.Color(63,63,0)); pixels.show(); delay(500);
      // blank
      pixels.setPixelColor(0, pixels.Color(0,0,0)); pixels.show(); delay(500); 
    }

    // green
    pixels.setPixelColor(0, pixels.Color(0,63,0));
    pixels.show(); 
    delay(3000);

    for (i=0; i<3; i++) {
      // orange
      pixels.setPixelColor(0, pixels.Color(63,40,0)); pixels.show(); delay(500);
      // blank
      pixels.setPixelColor(0, pixels.Color(0,0,0)); pixels.show(); delay(500); 
    }
}
