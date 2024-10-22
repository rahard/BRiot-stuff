#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

// Create an instance of the sensor
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup() {
  Serial.begin(9600);
  Wire.begin(D2, D1);  // Initialize I2C with SDA=D2 and SCL=D1
  
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  sensors_event_t event;
  bmp.getEvent(&event);
  
  if (event.pressure) {
    // Display the pressure in hPa
    Serial.print("Pressure: ");
    Serial.print(event.pressure);
    Serial.println(" hPa");

    // Calculate altitude (note that this is not true altitude, but the difference from sea level)
    float seaLevelPressure = 1013.25;  // Adjust to your local sea level pressure
    Serial.print("Altitude: ");
    Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
    Serial.println(" meters");
  } else {
    Serial.println("Sensor error");
  }

  delay(2000);  // Wait for 2 seconds before reading again
}
