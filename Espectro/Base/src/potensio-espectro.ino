#include <ESPectro.h>

ESPectro board;
uint32_t lastAnalogRead = 0;

void setup() {

    Serial.begin(9600);

    //Wait for Serial to be available
    while (!Serial);
}

void loop() {

    //Read analog value and voltage every 1 second
    if (millis() - lastAnalogRead > 1000) {
        Serial.print("A0 value = ");
        Serial.println(board.readAnalog());
        Serial.print("A0 voltage = ");
        Serial.print(board.readAnalogVoltage());
        Serial.println(" volt");

        lastAnalogRead = millis();
    }
}
