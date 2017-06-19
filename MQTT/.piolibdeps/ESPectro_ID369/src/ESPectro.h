//
// Created by Andri Yadi on 7/31/16.
//

#ifndef ESPECTROCORE_ESPECTRO_H
#define ESPECTROCORE_ESPECTRO_H

#include "Arduino.h"
#include "ESPectro_Constants.h"
#include <Ticker.h>
#include <functional>
#include <ESP8266WiFi.h>
#include "ESPectro_Neopixel.h"
#include "ESPectro_LED.h"

#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

//#include <exception>

enum ESPectro_Version { ESPectro_V2, ESPectro_V3};

class ESPectro {
public:
    ESPectro(ESPectro_Version v = ESPectro_V3);
    ~ESPectro();

    void run();

    //Analog
    int readAnalog();
    float readAnalogVoltage();

    //LED convenient methods
    ESPectro_LED &getLED();
    void turnOnLED();
    void turnOffLED();
    void blinkLED(uint32_t interval = 500, uint32_t count = UINT16_MAX);
    void fadeLED(uint32_t duration = 1000, uint32_t count = UINT16_MAX);
    void stopLEDAnimation();
    void toggleLED();

    //Neopixel convenient methods
    ESPectro_Neopixel_Default &getNeopixel();
    void turnOnNeopixel(NeoGrbFeature::ColorObject colorObject, uint16_t pixelNo = 0);
    void turnOffNeopixel(uint16_t pixelNo = 0);
    void turnOffAllNeopixel();

    //OTA
    void beginOTA();

private:
    ESPectro_LED *led_ = NULL;
    ESPectro_Neopixel_Default *neopixel_ = NULL;
    ESPectro_Version version_;

    ArduinoOTAClass *ota_ = NULL;
};



enum ESPectro_Button_State {
    ESPectroButtonUnknown,
    ESPectroButtonPressed,
    ESPectroButtonReleased,
    ESPectroButtonLongPressed
};

typedef std::function<void()> ButtonActionCallback;

class ESPectro_Button {
public:
    ESPectro_Button(ESPectro_Version v = ESPectro_V3, uint8_t gpio = ESPECTRO_BUTTON_PIN, boolean activeHigh = false);
    ~ESPectro_Button();

    void begin();
    ESPectro_Button_State getState();
    void run();
    void onButtonDown(ButtonActionCallback cb);
    void onButtonUp(ButtonActionCallback cb);
    void onPressed(ButtonActionCallback cb);
    void onLongPressed(ButtonActionCallback cb);
    void onDoublePressed(ButtonActionCallback cb);

    void setGpioNumber(uint8_t g) {
        gpioNumber_ = g;
    }

    static ESPectro_Button *GetInstance()
    {
        return ESPectro_Button::pESPButton;
    }

private:

    static ESPectro_Button *pESPButton;

    ESPectro_Version version_;
    uint8_t gpioNumber_;
    bool activeHigh_;
    ESPectro_Button_State buttonState_ = ESPectroButtonReleased;

    unsigned long lastButtonChangedMillis_  = 0, lastButtonPressedMillis_ = 0;

    ButtonActionCallback btnDownCallback_;
    ButtonActionCallback btnUpCallback_;
    ButtonActionCallback pressedCallback_;
    ButtonActionCallback longPressedCallback_;
    ButtonActionCallback doublePressedCallback_;

    bool isActive();
    uint8_t pressCount_ = 0;
};

#endif //ESPECTROCORE_ESPECTRO_H
