//
// Created by Andri Yadi on 3/17/17.
//

#include "DCX_AppSetting.h"

static bool needsSaving;

static uint16_t crc16ccitt(const uint8_t *buf, size_t len)
{
    //Serial.printf("Length: %d\n", len);

    /* Sanity check: */
    if(buf == NULL) {
        //Serial.println("Buffer is NULL");
        return 0;
    }

    unsigned char x;
    unsigned short crc = 0xFFFF;

    while (len--){
        x = crc >> 8 ^ *buf++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x <<5)) ^ ((unsigned short)x);
    }

    return crc;
}

void DCX_AppSetting::reset()  {

    if (exist()) {
        //remove file
        SPIFFS.remove(APP_SETTINGS_FILE);
        DEBUG_SERIAL("Removing file\r\n");
    }

    wifiConfigured = false;
    utc = 7;

    //memcpy(apName, SETTING_DEFAULT_AP_NAME, sizeof(SETTING_DEFAULT_AP_NAME));
    strcpy(apName, SETTING_DEFAULT_AP_NAME);
    apName[sizeof(SETTING_DEFAULT_AP_NAME) - 1] = '\0';

//        memcpy(apPass, SETTING_DEFAULT_AP_PASS, sizeof(SETTING_DEFAULT_AP_PASS));
//        apName[sizeof(apPass) - 1] = '\0';
    strcpy(apPass, SETTING_DEFAULT_AP_PASS);
    apPass[sizeof(SETTING_DEFAULT_AP_PASS) - 1] = '\0';
//

    memset(ssidName, 0, sizeof(ssidName) - 1);
    ssidName[sizeof(ssidName) - 1] = '\0';

    memset(ssidPass, 0, sizeof(ssidPass) - 1);
    ssidPass[sizeof(ssidName) - 1] = '\0';

}

bool DCX_AppSetting::load() {
    if (!SPIFFS.begin()) {
        DEBUG_SERIAL("SPIFFS init failed!\r\n");
        return false;
    }

//    if (SETTING_FORCE_INIT) {
//        DEBUG_SERIAL("Removing setting file\r\n");
//        SPIFFS.remove(APP_SETTINGS_FILE);
//    }

    if (exist())
    {
        File f = SPIFFS.open(APP_SETTINGS_FILE, "r");
        if (!f) {
            DEBUG_SERIAL("File open failed\r\n");
            return false;
        }

////            const int BUFFER_SIZE = JSON_OBJECT_SIZE(8);
////            StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
//            DynamicJsonBuffer jsonBuffer;
//
//            String jsonString = f.readString();
//            JsonObject& root = jsonBuffer.parseObject(jsonString);
//
//            JsonObject& config = root["config"];
//
//            ssidName = config["ssidName"].as<char*>();
//            ssidPass = config["ssidPass"].as<char*>();
//            ipAddr = IPAddress();
//            ipAddr.fromString(config["ipAddr"].as<char*>());
//
//            wifiConfigured = config["wifiConfigured"];
//            //configInited = config["configInited"];
//            apName = config["apName"].as<char*>();
//            apPass = config["apPass"].as<char*>();
//
//            utc = config["utc"];
//
//            //delete[] jsonString;

        f.read((uint8_t*)this, sizeof(AppSetting)/sizeof(uint8_t));

//        Serial.print(crc16, HEX);
//        Serial.println();

        // check header and CRC
        uint16_t calcCRC16 = crc16ccitt((uint8_t*)this, (uint32_t)&AppSetting.crc16 - (uint32_t)&AppSetting.crcHeader);
//        Serial.print(calcCRC16, HEX);
//        Serial.println();

        if (crcHeader != APP_SETTINGS_DEFAULT_HEADER || crc16 != calcCRC16 || crc16 == 0) {
            DEBUG_SERIAL("CRC Failed. Resetting....\n");
            reset();
            save(true);
        }

#if SETTING_FORCE_INIT
        reset();
        save(true);
#endif
    }
    else {
        reset();
        save(true);
    }

    return true;
}

bool DCX_AppSetting::save(bool forced) {

//        DynamicJsonBuffer jsonBuffer;
//
//        JsonObject& root = jsonBuffer.createObject();
//
//        JsonObject& config = jsonBuffer.createObject();
//        root["config"] = config;
//        config["ssidName"] = ssidName.c_str();
//        config["ssidPass"] = ssidPass.c_str();
//        config["ipAddr"] = ipAddr.toString();
//        config["wifiConfigured"] = wifiConfigured;
//        //config["configInited"] = configInited;
//        config["apName"] = apName.c_str();
//        config["apPass"] = apPass.c_str();
//        config["utc"] = utc;
//
//        //TODO: add direct file stream writing
//        String rootString;
//        root.printTo(rootString);
//
//        //fileSetContent(APP_SETTINGS_FILE, rootString);
//
//        File out = SPIFFS.open(APP_SETTINGS_FILE, "w+");
//        if (!out) {
//            DEBUG_SERIAL("Failed to open setting file for writing!\r\n");
//            return false;
//        }
//
//        out.print(rootString);

    if (!(needsSaving || forced)) {
        return false;
    }

    crcHeader = APP_SETTINGS_DEFAULT_HEADER;
    crc16 = crc16ccitt((uint8_t*)this, (uint32_t)&AppSetting.crc16 - (uint32_t)&AppSetting.crcHeader);

//    Serial.print(crc16, HEX);
//    Serial.println();

    DEBUG_SERIAL("[SETTING] Storing setting\n");

    File out = SPIFFS.open(APP_SETTINGS_FILE, "w+");
    if (!out) {
        DEBUG_SERIAL("Failed to open setting file for writing!\r\n");
        return false;
    }

    out.write((uint8_t*)this, sizeof(AppSetting)/sizeof(uint8_t));

    needsSaving = false;

    return true;
}

bool DCX_AppSetting::saveWiFiSettings(const char *sName, const char *sPass, IPAddress ipAddress) {

    strcpy(ssidName, sName);
    strcpy(ssidPass, sPass);
    strcpy(ipAddr, ipAddress.toString().c_str());

    needsSaving = true;

    return true;
}
