#include <SPI.h>
#include <LoRa.h>

// Define LoRa pins
#define SS 18
#define RST 14
#define DIO0 26

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0); // Set CS, reset, IRQ pins

  if (!LoRa.begin(915E6)) {  // Initialize LoRa with frequency 915 MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa initialized successfully.");
}

void loop() {
  Serial.println("Sending packet: Hello LoRa!");
  
  // Send LoRa packet
  LoRa.beginPacket();
  LoRa.print("Hello LoRa!");
  LoRa.endPacket();
  
  delay(5000);  // Wait for 5 seconds
}

