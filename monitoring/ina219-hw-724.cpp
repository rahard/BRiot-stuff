#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Initialize INA219 sensor
Adafruit_INA219 ina219;

// Initialize OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup(void) {
  Serial.begin(115200);

  // Initialize INA219 sensor
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  Serial.println("INA219 sensor initialized.");

  // Initialize OLED display
//  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {  // Default I2C address for Wemos Lolin32 OLED
//    Serial.println("Failed to initialize OLED display");
//    while (1) { delay(10); }
//  }
//  Serial.println("OLED display initialized.");

  // Start I2C Com SDA = 5 and SCL = 4 on Wemos Lolin32 ESP32 with built-in SSD1306 OLED
  Wire.begin(5, 4);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000); // Pause for 2 seconds

  // Clear the display buffer
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("INA219 Sensor");
  display.display();
  delay(2000);  // Display splash screen for 2 seconds
}

void loop(void) {
  // Read sensor data
  float shuntVoltage_mV = ina219.getShuntVoltage_mV();
  float busVoltage_V = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW();

  // Print to Serial Monitor
  Serial.print("Shunt Voltage: "); Serial.print(shuntVoltage_mV); Serial.println(" mV");
  Serial.print("Bus Voltage:   "); Serial.print(busVoltage_V); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

  // Display on OLED
  display.clearDisplay();
  display.setCursor(0, 0);

  // Display bus voltage
  display.print("Voltage: ");
  display.print(busVoltage_V, 2);  // Display with 2 decimal places
  display.println(" V");

  // Display current
  display.print("Current: ");
  display.print(current_mA, 2);  // Display with 2 decimal places
  display.println(" mA");

  // Display power
  display.print("Power:   ");
  display.print(power_mW, 2);  // Display with 2 decimal places
  display.println(" mW");

  // Update the display
  display.display();

  delay(2000);  // Wait for 2 seconds before the next reading
}
