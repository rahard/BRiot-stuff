//
// Created by Andri Yadi on 8/25/16.
//

#include "ESPectro_Neopixel.h"

template<typename T_COLOR_FEATURE, typename T_METHOD>
ESPectro_Neopixel<T_COLOR_FEATURE, T_METHOD>::ESPectro_Neopixel(uint16_t countPixels, uint8_t pin):
        NeoPixelBus<T_COLOR_FEATURE, T_METHOD>(countPixels, pin) {

}

//template<typename T_COLOR_FEATURE, typename T_METHOD>
//ESPectro_Neopixel<T_COLOR_FEATURE, T_METHOD>::~ESPectro_Neopixel() {
//
//}

//template<typename T_COLOR_FEATURE, typename T_METHOD>
//void ESPectro_Neopixel<T_COLOR_FEATURE, T_METHOD>::turnOn(typename T_COLOR_FEATURE::ColorObject colorObject) {
//    if (this->PixelCount() == 0) {
//        return;
//    }
//
//    this->SetPixelColor(0, colorObject);
//    this->Show();
//}
//
//template<typename T_COLOR_FEATURE, typename T_METHOD>
//void ESPectro_Neopixel<T_COLOR_FEATURE, T_METHOD>::turnOff() {
//    if (this->PixelCount() == 0) {
//        return;
//    }
//
//    this->SetPixelColor(0, HtmlColor(0x000000));
//    this->Show();
//}

ESPectro_Neopixel_Default::ESPectro_Neopixel_Default(uint16_t countPixels, uint8_t pin):
        ESPectro_Neopixel<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod>(countPixels, pin)  {

}

ESPectro_Neopixel_Default::~ESPectro_Neopixel_Default() {

}


ESPectro_Neopixel_UART::ESPectro_Neopixel_UART(uint16_t countPixels, uint8_t pin):
        ESPectro_Neopixel<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod>(countPixels, pin){

}

ESPectro_Neopixel_UART::~ESPectro_Neopixel_UART() {

}


ESPectro_Neopixel_DMA::ESPectro_Neopixel_DMA(uint16_t countPixels, uint8_t pin):
        ESPectro_Neopixel<NeoGrbFeature, NeoEsp8266Dma400KbpsMethod>(countPixels, pin){

}

ESPectro_Neopixel_DMA::~ESPectro_Neopixel_DMA() {

}

