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
    delay(2000);

    for (i=0; i<5; i++) {
      // blank
      pixels.setPixelColor(0, pixels.Color(0,0,0)); pixels.show(); delay(500); 
      // yellow
      pixels.setPixelColor(0, pixels.Color(63,30,0)); pixels.show(); delay(500);
    }

    // blank
    pixels.setPixelColor(0, pixels.Color(0,0,0)); pixels.show(); delay(500); 
    // green
    pixels.setPixelColor(0, pixels.Color(0,40,0));
    pixels.show(); 
    delay(2000);

    for (i=0; i<3; i++) {
      // blank
      pixels.setPixelColor(0, pixels.Color(0,0,0)); pixels.show(); delay(500); 
      // yellow
      pixels.setPixelColor(0, pixels.Color(63,30,0)); pixels.show(); delay(500);
    }
}
