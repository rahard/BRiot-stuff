/*
  Initial example of OTA flashing

  Created by 22 Sep 2016
  by Andri Yadi
*/

#include <ESPectro.h>
#include <DCX_AppSetting.h>
#include <DCX_WifiManager.h>

ESPectro board(ESPectro_V3);
ESPectro_Button button(ESPectro_V3);
DCX_WifiManager wifiManager(AppSetting);

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(115200);

    //Wait Serial to be ready
    while (!Serial);
    delay(2000);

    DEBUG_SERIAL("\r\nInitializing...\r\n\r\n");
    
    AppSetting.load();
    AppSetting.debugPrintTo(Serial);

    //Just in case RGB neopixel is light up, turn all off
    board.turnOffAllNeopixel();

    button.begin();

    button.onButtonDown([]() {
        //board.turnOnLED();
        //neopixel.turnOn(HtmlColor(0x0000ff));

        Serial.println(F("Considered button down"));
    });

    button.onLongPressed([]() {
        Serial.println(F("Considered Long Pressed"));
        //wifiManager.startSmartConfig();
    });

    button.onButtonUp([]() {
        //board.turnOffLED();
        //neopixel.turnOff();

        Serial.println(F("Considered button up"));
    });

//    button.onPressed([]() {
//        Serial.println(F("Considered Pressed"));
//    });

    button.onDoublePressed([]() {
        Serial.println(F("Considered Double Pressed"));

        if (WiFi.isConnected()) {
            board.beginOTA();
            board.fadeLED(1200);
        }
    });
    
    wifiManager.onWifiConnectStarted([]() {
        DEBUG_SERIAL("WIFI CONNECTING STARTED\r\n");
        board.fadeLED(700);
    });

    wifiManager.onWifiConnected([](boolean newConn) {
        DEBUG_SERIAL("WIFI CONNECTED\r\n");
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
    //wifiManager.begin();
    wifiManager.begin("DyWare-AP3", "p@ssw0rd");
}

// the loop function runs over and over again forever
void loop() {
    wifiManager.run();
    board.run();
    button.run();
}
