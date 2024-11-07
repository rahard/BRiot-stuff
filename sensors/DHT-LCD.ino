// Temperature and Humidity shown on LCD
// BR 2024
#include "DHT.h"

#define DHTPIN D4     // what digital pin we're connected to
// #define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

// LCD stuff
// add this in platformio.ini
// lib_deps = marcoschwartz/LiquidCrystal_I2C@^1.1.4
#include <LiquidCrystal_I2C.h>
// set the LCD address to 0x3F or 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,16,2);



void setup() {
  Serial.begin(9600);
  dht.begin();
  // init LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Kadang membutuhkan 2 detik
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("\n");

  // output to LCD
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Humid: ");
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(t);
}
