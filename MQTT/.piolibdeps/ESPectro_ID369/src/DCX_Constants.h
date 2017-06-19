//
// Created by Andri Yadi on 8/26/16.
//

#ifndef DYCODEX_CONSTANTS_H
#define DYCODEX_CONSTANTS_H

#define DEBUG_SERIAL(...)   Serial.printf( __VA_ARGS__ )

#ifndef DEBUG_SERIAL
#define DEBUG_SERIAL(...)
#else
#define DEBUG_SERIAL_LN     Serial.println()
#endif

#define SETTING_DEFAULT_AP_NAME             "ESPectro_000"
#define SETTING_DEFAULT_AP_PASS             "11223344"
#define SETTING_FORCE_INIT                  false

#define WIFI_CONNECTING_INTERVAL            500

#endif //DYCODEX_CONSTANTS_H
