/* Sensor web server 
2024 @rahard
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "DHT.h"
#define DHTPIN 2 /* wemos DHT11 shield */
#define DHTTYPE DHT22

// Replace with your network credentials
#define WIFISSID "wifiSSID"
#define WIFIPASS "wifipass"

const char* deviceid="ID=yourDEVICEID";
const char* groupid="GROUP=yourGROUP";
// server to receive the data
const char* host="the.server";
const int port=80;

// do not touch below
DHT dht(DHTPIN, DHTTYPE);
unsigned long startTime = millis();


const int watchdog = 10000; // delay before pushing data
unsigned long previousMillis = millis();

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

}
 
void loop(void){
   unsigned long currentMillis = millis();
   if (currentMillis - previousMillis > watchdog) {
      previousMillis = currentMillis;


      WiFiClient client;
      HTTPClient http;

    //   if (!client.connect(host,port)) {
    //      Serial.print("cannot connect to web server ");
    //      Serial.println(host);
    //      return;
    //   }

      // get data from sensor
      float t = dht.readTemperature();     // celcius
      float f = dht.readTemperature(true); // fahrenheit
      float h = dht.readHumidity();
      if ( isnan(t) || isnan(f) || isnan(h) ) {
         Serial.println("Failed to read DHT sensor");
         return;
      }

      //String url="/weather/poller.php?";
      String url = "http://";
      url += host;
      url += ":";
      url += port;
      url += "/?";
      //url += "ID=YOURID";
      url += deviceid;
      url += "&";
      url += groupid;
      url += "&temperature=";
      url += String(t);
      url += "&humidity=";
      url += String(h);
      url += "&softwaretype=BRIotv2";
      //url += WiFi.localIP().toString();
      //url += "&time=";
      //url += String(millis());

      // send it

      Serial.println(url);

      http.begin(client, url);
      int httpResponseCode = http.GET();

      String payload = "{}";

      if (httpResponseCode > 0) {
        Serial.print("Http resp code:");
        Serial.println(httpResponseCode);
        payload = http.getString();
      } 
      else {
        Serial.print("err code:");
        Serial.println(httpResponseCode);
      }

      http.end();
   }
}
