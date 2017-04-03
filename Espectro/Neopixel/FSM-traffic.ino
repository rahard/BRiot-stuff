/* traffic light with FSM */
/* Budi Rahardjo @rahard 2017 */

#include <Adafruit_NeoPixel.h>
#define PIN 15
#define NUMPIXELS 1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int state=0; // 0=red, 1=yellow1, 2=green; 3=yellow2
int delay0=3000;
int delay1=1000;
int delay2=3000;
int delay3=2000;
unsigned long lastTime=0;
unsigned long elapsed=0;

void setup() {
  pixels.begin();
  state=1; // start with red
  lastTime = millis(); //
  Serial.begin(9600);
}

void loop() {
  elapsed = millis() - lastTime;
  // if red -> yellow1
  if ((state==0) && (elapsed > delay0)) {
    state=1;
    lastTime = millis();
    elapsed=0;
    pixels.setPixelColor(0, 63, 30, 0);
    pixels.show();
    Serial.println("yellow1");
  }
  // yellow1 -> green
  if ((state==1) && (elapsed > delay1)) {
    state=2;
    lastTime = millis();
    elapsed=0;
    pixels.setPixelColor(0, 0, 63, 0);
    pixels.show();
    Serial.println("green");
  }
  // green -> yellow2
  if ((state==2) && (elapsed > delay2)) {
    state=3;
    lastTime = millis();
    elapsed=0;
    pixels.setPixelColor(0, 63, 30, 0);
    pixels.show();
    Serial.println("yellow2");
  }
  // yellow2 -> red
  if ((state==3) && (elapsed > delay3)) {
    state=0;
    lastTime = millis();
    elapsed=0;
    pixels.setPixelColor(0, 63, 0, 0);
    pixels.show();
    Serial.println("red");
  }
  Serial.println("unknown state");
}
