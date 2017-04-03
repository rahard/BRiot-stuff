//
// Created by Andri Yadi on 9/1/16.
//

#ifndef DYCODEX_NEOPIXEL_ANIMATION_H
#define DYCODEX_NEOPIXEL_ANIMATION_H


#include "ESPectro_Neopixel.h"
#include <NeoPixelAnimator.h>
#include <functional>

typedef std::function<void()> AnimationCompletedCallback;

class DCX_Neopixel_Animation {
public:
    DCX_Neopixel_Animation(ESPectro_Neopixel_Default &neopixel);
    ~DCX_Neopixel_Animation();
    void start();
    void end();
    void run();
    void onAnimationCompleted(AnimationCompletedCallback cb);

protected:
    ESPectro_Neopixel_Default &neopixel_;
    NeoPixelAnimator *animator_ = NULL;

    boolean animationPrevStarted_ = false;
    AnimationCompletedCallback animCompletedCb_;
};


class DCX_Neopixel_PulseAnimation: public DCX_Neopixel_Animation {
public:
    DCX_Neopixel_PulseAnimation(ESPectro_Neopixel_Default &neopixel, RgbColor &toColor);
    ~DCX_Neopixel_PulseAnimation();
    void start();
    void end();
    void setPulsingToColor(RgbColor &toColor);
    void setPulsingInterval(uint16_t pulsingInterval);
private:
    uint16_t pulsingAnimationState_ = 0;
    RgbColor& pulsingToColor_;
    uint16_t pulsingInterval_ = 1000;
};


class DCX_Neopixel_CyclonAnimation: public DCX_Neopixel_Animation {
public:
    DCX_Neopixel_CyclonAnimation(ESPectro_Neopixel_Default &neopixel);
    ~DCX_Neopixel_CyclonAnimation();
    void start();
    void end();
//    void run();
//    void onAnimationCompleted(AnimationCompletedCallback cb);
    void setAnimationDirection(bool up);

private:
//    ESPectro_Neopixel_Default &neopixel_;
//    NeoPixelAnimator *animator_ = NULL;
//
//    boolean animationPrevStarted_ = false;
//
//    AnimationCompletedCallback animCompletedCb_;

    uint16_t lastPixel_ = 0; // track the eye position
    int8_t moveDir_ = 1;

    void fadeAll(uint8_t darkenBy);
    void setPixelColor(uint16_t idx);
};


#endif //DYCODEX_NEOPIXEL_ANIMATION_H
