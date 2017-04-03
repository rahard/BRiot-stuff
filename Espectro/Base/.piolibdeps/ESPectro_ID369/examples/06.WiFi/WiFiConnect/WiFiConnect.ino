/*
  Connecting to WiFi with an easy WifiManager class.

  Created by 22 Sep 2016
  by Andri Yadi
*/

#include <ESPectro.h>
#include <DCX_AppSetting.h>
#include <DCX_WifiManager.h>

ESPectro board;

// Create wifiManager object by passing AppSetting object.
// AppSetting is object that stores WiFi setting (SSID name and password)
DCX_WifiManager wifiManager(AppSetting);

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(115200);

    //Wait Serial to be ready
    while (!Serial);

    DEBUG_SERIAL("\r\nInitializing...\r\n\r\n");

    //Load last stored setting
    AppSetting.load();
    //Optionally, log current setting to Serial
    AppSetting.debugPrintTo(Serial);

    //Just in case RGB neopixel is light up, turn all off
    board.turnOffAllNeopixel();

    wifiManager.onWifiConnectStarted([]() {
        DEBUG_SERIAL("WIFI CONNECTING STARTED\r\n");
        //Start LED fading animation upon connection start
        board.fadeLED(700);
    });

    wifiManager.onWifiConnected([](boolean newConn) {
        DEBUG_SERIAL("WIFI CONNECTED. IP Address: %s\r\n", WiFi.localIP().toString().c_str());
        board.stopLEDAnimation();
    });

    wifiManager.onWifiConnecting([](unsigned long elapsed) {
        //DEBUG_SERIAL("%d\r\n", elapsed);
    });

    wifiManager.onWifiDisconnected([](WiFiDisconnectReason reason) {
        DEBUG_SERIAL("WIFI GIVE UP\r\n");
        board.stopLEDAnimation();
    });

    //wifiManager.begin("your-ssid-name", "your-ssid-password");

    //Alternatively, you can just begin and use ESP8266 Smart Config iOS/Android app to configure WiFi
    //I recommend to use this Android app: https://play.google.com/store/apps/details?id=com.cmmakerclub.iot.esptouch
    wifiManager.begin();

}

// the loop function runs over and over again forever
void loop() {
    wifiManager.run();
}
