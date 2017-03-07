#include <Adafruit_NeoPixel.h>

#define PIN            15
#define NUMPIXELS      1 

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 1000;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

    // red
    pixels.setPixelColor(0, pixels.Color(150,0,0));
    pixels.show(); 
    delay(5000);

    for (i=0; i<5; i++) {
    // yellow
    pixels.setPixelColor(0, pixels.Color(255,100,0));
    pixels.show(); 
    delay(2000);
    // blank
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show(); 
    delay(2000);
    }

    // green
    pixels.setPixelColor(0, pixels.Color(0,0,150));
    pixels.show(); 
    delay(5000);
    // yellow
    pixels.setPixelColor(0, pixels.Color(255,100,0));
    pixels.show(); 
    delay(2000);
}
