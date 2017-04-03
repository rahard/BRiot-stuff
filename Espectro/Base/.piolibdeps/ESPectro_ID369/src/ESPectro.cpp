//
// Created by Andri Yadi on 7/31/16.
//

#include <c_types.h>
#include "ESPectro.h"

ESPectro::ESPectro(ESPectro_Version v):version_(v) {

}

ESPectro::~ESPectro() {
    if (led_ != NULL) {
        delete led_;
        led_ = NULL;
    }

    if (neopixel_ != NULL) {
        delete neopixel_;
        neopixel_ = NULL;
    }

    if (ota_ != NULL) {
        delete ota_;
        ota_ = NULL;
    }
}

void ESPectro::run() {
    if (ota_ != NULL) {
        ota_->handle();
    }
}

void ESPectro::turnOnLED() {
    getLED().turnOn();
}

void ESPectro::turnOffLED() {
    getLED().turnOff();
}

void ESPectro::blinkLED(uint32_t interval, uint32_t count) {
    getLED().blink(interval, count);
}

void ESPectro::fadeLED(uint32_t duration, uint32_t count) {
    getLED().fade(duration);
}

ESPectro_LED &ESPectro::getLED() {
    if (led_ == NULL) {
        led_ = new ESPectro_LED();
        led_->begin();
    }

    return *led_;
}

void ESPectro::stopLEDAnimation() {
//    getLED().stopBlink();
    getLED().stopAnimation();
}

void ESPectro::toggleLED() {
    getLED().toggle();
}

ESPectro_Neopixel_Default &ESPectro::getNeopixel() {
    if (neopixel_ == NULL) {
        if (version_ >= ESPectro_V3) {
            neopixel_ = new ESPectro_Neopixel_Default(3, ESPECTRO_NEOPIXEL_PIN_V3);
        } else {
            neopixel_ = new ESPectro_Neopixel_Default(1, ESPECTRO_NEOPIXEL_PIN);
        }
        neopixel_->Begin();
    }

    return *neopixel_;
}

void ESPectro::turnOnNeopixel(NeoGrbFeature::ColorObject colorObject, uint16_t pixelNo) {
    getNeopixel().turnOn(colorObject, pixelNo);
}

void ESPectro::turnOffNeopixel(uint16_t pixelNo) {
    getNeopixel().turnOff(pixelNo);
}

void ESPectro::turnOffAllNeopixel() {
    for(uint16_t i = 0; i < getNeopixel().PixelCount(); i++) {
        getNeopixel().turnOff(i);
    }
}

int ESPectro::readAnalog() {
    return analogRead(A0);
}

float ESPectro::readAnalogVoltage() {
    float voltage = readAnalog() * (3.3f / 1023.0f);
    return voltage;
}

void ESPectro::beginOTA() {
    if (ota_ == NULL) {
        ota_ = new ArduinoOTAClass();
    }

    ota_->setHostname(SETTING_DEFAULT_AP_NAME);

    ota_->onStart([this]() {
        this->turnOnLED();
    });

    ota_->onEnd([this]() {
        this->stopLEDAnimation();
        this->blinkLED(300, 3);
    });

    ota_->onError([this](ota_error_t error) {
        this->stopLEDAnimation();
        ESP.restart();
    });

    ota_->onProgress([](unsigned int progress, unsigned int total) {
        DEBUG_SERIAL("Progress: %u%%\r\n", (progress / (total / 100)));
    });

    Serial.println(F("Beginning OTA"));
    ota_->begin();
}


/* the global instance pointer */
ESPectro_Button *ESPectro_Button::pESPButton = NULL;
static volatile bool ESPectro_Button_Value_Changed = false;
static volatile bool ESPectro_Button_RunAlreadyCalled_ = false;

ESPectro_Button::ESPectro_Button(ESPectro_Version v, uint8_t gpio, boolean activeHigh):
        gpioNumber_(gpio), activeHigh_(activeHigh), version_(v)

{
    if (gpio == ESPECTRO_BUTTON_PIN && v == ESPectro_V3) {
        gpioNumber_ = ESPECTRO_BUTTON_PIN_V3;
    }
}

ESPectro_Button::~ESPectro_Button() {

}

void ESPectro_Button_Interrupt() {
    ESPectro_Button_Value_Changed = true;
    //Serial.printf("Button triggered %d\r\n", digitalRead(ESPECTRO_BUTTON_PIN));

    if (!ESPectro_Button_RunAlreadyCalled_) {
        ESPectro_Button *const pESPButton = ESPectro_Button::GetInstance();
        //ASSERT(pESPButton != NULL);

        pESPButton->run();
    }
}

void ESPectro_Button::begin() {

    //ASSERT(ESPectro_Button::pESPButton == this || ESPectro_Button::pESPButton == NULL);
    ESPectro_Button::pESPButton = this;

    //Serial.printf("Button gpio %d\r\n", gpioNumber_);

    pinMode(gpioNumber_, activeHigh_ ? INPUT_PULLDOWN_16 : INPUT_PULLUP);
    if (gpioNumber_ != 16) {
        attachInterrupt(gpioNumber_, ESPectro_Button_Interrupt, CHANGE);
    }
    else {
        Serial.println(F("Unsupported pin for interrupt"));
    }
//    else {
//        throw std::runtime_error("fatal error");
//    }
}

void ESPectro_Button::onPressed(ButtonActionCallback cb) {
    //btnDownCallback_ = cb;
    pressedCallback_ = cb;
}

void ESPectro_Button::onButtonDown(ButtonActionCallback cb) {
    btnDownCallback_ = cb;
}

void ESPectro_Button::onButtonUp(ButtonActionCallback cb) {
    btnUpCallback_ = cb;
}

void ESPectro_Button::onLongPressed(ButtonActionCallback cb) {
    longPressedCallback_ = cb;
}

void ESPectro_Button::onDoublePressed(ButtonActionCallback cb) {
    doublePressedCallback_ = cb;
}

ESPectro_Button_State ESPectro_Button::getState() {
    return ESPectroButtonReleased;
}

void ESPectro_Button::run() {

    ESPectro_Button_RunAlreadyCalled_ = true;
    unsigned long currentMillis = millis();

    if (!ESPectro_Button_Value_Changed) {

        if ((currentMillis - lastButtonPressedMillis_ > ESPECTRO_BUTTON_LONG_PRESS_DURATION_MS)) {

            if (buttonState_ == ESPectroButtonPressed) {
                buttonState_ = ESPectroButtonLongPressed;
                //Serial.println(F("Considered Long Pressed"));
                if (longPressedCallback_) {
                    longPressedCallback_();
                }
            }
            pressCount_ = 0;
        }
    }
    else {

        ESPectro_Button_Value_Changed = false;

        if ((currentMillis - lastButtonChangedMillis_) > ESPECTRO_BUTTON_DEBOUNCE_DURATION_MS) {
            lastButtonChangedMillis_ = currentMillis;
        }
        else {
            //Serial.println(F("Debounced"));
            return;
        }

        boolean pressed = isActive();
        if (pressed) {
            lastButtonPressedMillis_ = currentMillis;
            //lastButtonChangedMillis_ = currentMillis;
            buttonState_ = ESPectroButtonPressed;
            //Serial.println(F("Pressed"));
            if (btnDownCallback_) {
                btnDownCallback_();
            }
        }
        else {
            //lastButtonReleasedMillis_ = currentMillis;
            //Serial.println(F("Released"));

            if (btnUpCallback_) {
                btnUpCallback_();
            }

            if (buttonState_ != ESPectroButtonLongPressed && currentMillis - lastButtonPressedMillis_ > ESPECTRO_BUTTON_PRESS_DURATION_MS) {
                buttonState_ = ESPectroButtonReleased;
                if (pressedCallback_) {
                    pressedCallback_();
                }

                pressCount_++;
                //Serial.printf("Pressed count %d\n", pressCount_);
                if (pressCount_ == 2) {
                    if (doublePressedCallback_) {
                        doublePressedCallback_();
                    }
                }
            }
        }
    }
}


bool ESPectro_Button::isActive() {
    int buttonState = digitalRead(gpioNumber_);
    boolean pressed = activeHigh_ ? buttonState == HIGH : buttonState == LOW;
    return pressed;
}


