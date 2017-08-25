/* Sensor web server 
@rahard
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// Replace with your network credentials
#define WIFISSID "brriset"
#define WIFIPASS "secret"

#include "DHT.h"
#define DHTPIN 2 /* wemos DHT11 shield */
#define DHTTYPE DHT11 


// do not touch below
DHT dht(DHTPIN, DHTTYPE);
unsigned long startTime = millis();

const char* host="167.205.4.34";
const int port=80;

const int watchdog = 20000; // delay before pushing data
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

      if (!client.connect(host,port)) {
         Serial.print("cannot connect to web server ");
         Serial.println(host);
         return;
      }

      // get data from sensor
      float t = dht.readTemperature();     // celcius
      float f = dht.readTemperature(true); // fahrenheit
      float h = dht.readHumidity();
      if ( isnan(t) || isnan(f) || isnan(h) ) {
         Serial.println("Failed to read DHT sensor");
         return;
      }

      String url="/weather/poller.php?";
      url += "ID=BRPAUME1";
      url += "&tempf=";
      url += String(f);
      url += "&humidity=";
      url += String(h);
      url += "&softwaretype=BRIotv1";
      url += "&action=updateraw";
      url += "&realtime=1&rtfreq=5";
      //url += WiFi.localIP().toString();
      //url += "&time=";
      //url += String(millis());

      // send it
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "Connection: close\r\n\r\n");

      // wait for respond
      unsigned long timeout = millis();
      while (client.available() == 0) {
         if (millis() - timeout > 5000) {
            Serial.print("timeout");
            client.stop();
            return;
         }
      }

      // ok, we got the reply
      while (client.available()) {
         String line = client.readStringUntil('\r');
         Serial.print(line);
      }
   }
}
