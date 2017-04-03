//
// Created by Andri Yadi on 8/25/16.
//

#ifndef DYCODEX_APPSETTING_H
#define DYCODEX_APPSETTING_H

#include <Arduino.h>
//#include <ArduinoJson.h>
#include <FS.h>
#include <IPAddress.h>
#include "DCX_Constants.h"

#define APP_SETTINGS_FILE "/espectro_setting.json" // leading point for security reasons :)
#define APP_SETTINGS_DEFAULT_HEADER 0xD4CD

struct DCX_AppSetting
{
//    String ssidName;
//    String ssidPass;
//    IPAddress ipAddr;

    bool wifiConfigured = false;
    //bool configInited = false;
//    String apName = String(SETTING_DEFAULT_AP_NAME);
//    String apPass = String(SETTING_DEFAULT_AP_PASS);
    uint16_t utc = 7;

    char ssidName[32+1];
    char ssidPass[32+1];
    char apName[32+1];
    char apPass[32+1];
    char ipAddr[16];

    uint16_t crcHeader;
    uint16_t crc16;

    void reset();
    bool load();
    bool save(bool forced = true);

    void debugPrintTo(Print &p) {
        p.printf("wifiConfigured: %d\r\n", wifiConfigured);
        p.printf("apName: %s\r\n", apName);
        p.printf("ssidName: %s\r\n", ssidName);
        p.printf("ipAddr: %s\r\n", ipAddr);
        p.printf("utc: %d\r\n", utc);
    }

    void parse(String jsonMessage)
    {
////        const int BUFFER_SIZE = JSON_OBJECT_SIZE(8);
////        StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
//        DynamicJsonBuffer jsonBuffer;
//
//        JsonObject& root = jsonBuffer.parseObject(jsonMessage);
//
//        JsonObject& config = root["config"];
//
//        if (config.containsKey("ssidName")) {
//            ssidName = config["ssidName"].as<char*>();
//        }
//        if (config.containsKey("utc")) {
//            utc = config["utc"];
//        }
    }

    bool saveWiFiSettings(const char *sName, const char *sPass, IPAddress ipAddress);

    bool exist() { return SPIFFS.exists(APP_SETTINGS_FILE); }
};

static DCX_AppSetting AppSetting;

#endif //DYCODEX_APPSETTING_H


