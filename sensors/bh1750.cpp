#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup(){
  Serial.begin(9600);

  // Initialize the I2C bus
  Wire.begin();
  // On esp8266: select SCL and SDA pins using Wire.begin(D4, D3);
  // Wemos/Lolin D1 Mini Pro and the Ambient Light shield: Wire.begin(D2, D1);

  lightMeter.begin();

  Serial.println(F("BH1750 begin"));
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}
