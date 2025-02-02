#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    // Wait for serial port to connect (for native USB)
    delay(1);
  }

  // Initialize the INA219 sensor
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  Serial.println("INA219 sensor initialized.");
}

void loop(void) {
  // Read shunt voltage (in mV)
  float shuntVoltage_mV = ina219.getShuntVoltage_mV();

  // Read bus voltage (in V)
  float busVoltage_V = ina219.getBusVoltage_V();

  // Read current (in mA)
  float current_mA = ina219.getCurrent_mA();

  // Read power (in mW)
  float power_mW = ina219.getPower_mW();

  // Print the results
  Serial.print("Shunt Voltage: "); Serial.print(shuntVoltage_mV); Serial.println(" mV");
  Serial.print("Bus Voltage:   "); Serial.print(busVoltage_V); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

  delay(1000); // Wait for 1 seconds before the next reading
}
