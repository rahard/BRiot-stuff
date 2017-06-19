//
// Created by Andri Yadi on 8/25/16.
//

#ifndef DYCODEX_WIFIMANAGER_H
#define DYCODEX_WIFIMANAGER_H

#include <Arduino.h>
#include "DCX_AppSetting.h"
#include <ESP8266WiFi.h>
#include <functional>

extern "C" {
#include "user_interface.h"
#include "include/wl_definitions.h"
}

typedef std::function<void()> WifiConnectionCallback;
typedef std::function<void(boolean)> WifiConnectedCallback;
typedef std::function<void(WiFiDisconnectReason)> WifiDisconnectedCallback;
typedef std::function<void(unsigned long elapsedTime)> WifiConnectingCallback;

class DCX_WifiManager {
public:
    DCX_WifiManager(DCX_AppSetting &setting);
    ~DCX_WifiManager();

    void begin();
    void begin(const char* ssid, const char *passphrase);
    void run();

    //void setConnectedDelegate(ConnectionDelegate connectedDelegate);
    void startSmartConfig();

    void onWifiConnectStarted(WifiConnectionCallback cb);
    void onWifiConnected(WifiConnectedCallback cb);
    void onWifiDisconnected(WifiDisconnectedCallback cb);
    void onWifiConnecting(WifiConnectingCallback cb);

    bool isWifiConnected();


    void setWifiConnecting();

private:
    DCX_AppSetting &setting_;

    void wifiDidConnected();
    void wifiDidDisconnected(WiFiDisconnectReason reason);

    //volatile boolean wifiConnectRequested_ = false;
//    volatile boolean connectedToWifi_ = false;
//    volatile boolean connectingToWifi_ = false;

    boolean  smartConfigRequested_ = false;
    byte wifiConnTrial_ = 0;

    volatile unsigned long wifiConnCheckingMillis_ = 0, wifiConnectStartMillis_ = 0;

    WifiConnectionCallback wifiConnectStartedCallback_;
    WifiConnectedCallback wifiConnectedHandler_;
    WifiDisconnectedCallback wifiDisconnectedHandler_;
    WifiConnectingCallback wifiConnectingCallback_;

    WiFiEventHandler connectedEventHandler_, disconnectedEventHandler_, gotIPEventHandler_;

    void tryToConnectWifi();
};


#endif //DYCODEX_WIFIMANAGER_H
