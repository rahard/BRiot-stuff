/* Sensor web server 
@rahard
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// Replace with your network credentials
#define WIFISSID "sniffer"
#define WIFIPASS "sniffer"

#include "DHT.h"
#define DHTPIN 14 /* sensor is connected to pin 14 of NodeMCU */
#define DHTTYPE DHT11   // type of sensor we're using


// do not touch below
unsigned long startTime = millis();

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);

String webPage = "";


void connectWifi() {
   Serial.println("Connecting to access point");
   WiFi.disconnect();
   if (WiFi.getMode() != WIFI_STA) {
      WiFi.mode(WIFI_STA);
   }
   WiFi.begin (WIFISSID, WIFIPASS );
   // ... Give ESP 10 seconds to connect to station.
   startTime = millis();
   while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
     delay(1000);
     Serial.print(".");
   }
   Serial.println("");
   // Check connection
   if (WiFi.status() == WL_CONNECTED) {
      Serial.print("WiFi connected; IP address: ");
      Serial.println(WiFi.localIP());
   } else {
      Serial.print("WiFi connect failed to ssid: ");
      Serial.println(WIFISSID);
   }
}

void setup(void){  
  Serial.begin(9600);
  dht.begin(); /* start sensor */
  delay(1000);
  connectWifi(); //make connection
  Serial.println("");


  server.on("/", [](){
    webPage="<H1>LED Status</H1>";
    webPage+="okay";
    server.send(200, "text/html", webPage);
    ESP.getFreeHeap();
  });

  server.on("/temp", [](){
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    server.send(200, "text/plain", (String)t);
    ESP.getFreeHeap();
  });
  
  //reset all LEDs
  server.on("/humidity", [](){
    float h = dht.readHumidity();
    server.send(200, "text/plain", (String)h);
    ESP.getFreeHeap();
  });

  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
}
