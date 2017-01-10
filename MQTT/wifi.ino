// Example to connect Espectro to WiFi
// code taken from places
// public domain
// Budi Rahardjo @rahard 2016


#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

int z=0;

void setup() {
    Serial.begin(9600);
    delay(1000);

    WiFiMulti.addAP("MyAccessPoint", "MyPassword");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
        // just to limit the tries ... so that I doesnt loop forever
        z++;
        if (z>100) {
           Serial.println("Fail connecting. Exiting");
           return;
           }
    }

    // yayyy we are connected
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}

void loop() {
}
