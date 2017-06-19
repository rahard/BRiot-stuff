//
// Created by Andri Yadi on 3/17/17.
//

#include "ESPectro_LED.h"

ESPectro_LED::ESPectro_LED(byte pin, boolean activeHigh): pin_(pin), activeHigh_(activeHigh) {
}

ESPectro_LED::~ESPectro_LED() {
    if (animTicker_ != NULL) {
        animTicker_->detach();
        delete animTicker_;
        animTicker_ = NULL;
    }

    if (animator_ != NULL) {
        delete animator_;
        animator_ = NULL;
    }
}

void ESPectro_LED::begin() {
    pinMode(ESPECTRO_LED_PIN, OUTPUT);
    turnOff();
}

void ESPectro_LED::turnOn() {
    digitalWrite(pin_, activeHigh_? HIGH: LOW);
}

void ESPectro_LED::turnOff() {
    digitalWrite(pin_, activeHigh_? LOW: HIGH);
}

boolean ESPectro_LED::isOn() {
    int val = digitalRead(pin_);
    return activeHigh_? (val == HIGH): (val == LOW);
}

byte ESPectro_LED::getPin() {
    return pin_;
}

void doAnimation(ESPectro_LED *led) {
    led->updateAnimation();
}

void ESPectro_LED::toggle() {
    if (isOn()) {
        turnOff();
    }
    else {
        turnOn();
    }
}

void ESPectro_LED::blink(uint32_t interval, uint32_t count) {

    stopAnimation();
    setAnimationTimeout(interval*count);

    animator_ = new ESPectro_LED_Animator();
    animator_->initPWM(pin_);

    animator_->setAnimation(ESPectro_LED_Animator::ESPectro_LED_Animation_Blink, interval);

    startAnimation();
}

void ESPectro_LED::fade(uint32_t duration, uint32_t count) {

    stopAnimation();
    setAnimationTimeout(count*duration);

    animator_ = new ESPectro_LED_Animator();
    animator_->initPWM(pin_);

    animator_->setAnimation(ESPectro_LED_Animator::ESPectro_LED_Animation_Fading, duration);

    startAnimation();
}

void ESPectro_LED::setAnimation(ESPectro_LED_Animator::ESPectro_LED_AnimationType animType, uint32_t speed, uint32_t count) {
    stopAnimation();
    setAnimationTimeout(count*speed);

    animator_ = new ESPectro_LED_Animator();
    animator_->initPWM(pin_);

    animator_->setAnimation(animType, speed);

    startAnimation();
}

void ESPectro_LED::startAnimation() {
    if (animTicker_ == NULL) {
        animTicker_ = new Ticker();
    }

    if (animator_ == NULL) {
        animator_ = new ESPectro_LED_Animator();
        animator_->initPWM(pin_);
    }

    animating_ = true;
    startAnimationTime_ = millis();

    animTicker_->detach();
    delay(10);
    animTicker_->attach_ms(10, doAnimation, this);
}

void ESPectro_LED::stopAnimation() {

    if (!animating_) { return; }

    animating_ = false;

    if (animator_ != NULL) {
        analogWrite(pin_, 0);

        delete animator_;
        animator_ = NULL;
    }

    if (animTicker_ != NULL) {
        animTicker_->detach();
        delete animTicker_;
        animTicker_ = NULL;
    }

    //black all
    turnOff();
}

bool ESPectro_LED::isAnimating() const {
    return animating_;
}

void ESPectro_LED::setAnimationTimeout(unsigned long timeOut) {
    animationTimeOut_ = timeOut;
}

void ESPectro_LED::updateAnimation() {
    if (!animating_)
        return;

    unsigned long now = millis();

    if (now - startAnimationTime_ >= animationTimeOut_) {
        stopAnimation();
        return;
    }

    animator_->runAnimation();
}


ESPectro_LED_Animator::ESPectro_LED_Animator() {
    maxOut_ = 0xFFFFFF;
    speed_ = 1000;
    lastRefreshTime_ = 0;
    refreshMillis_ = 1000/50;
}

ESPectro_LED_Animator::~ESPectro_LED_Animator() {

}

void ESPectro_LED_Animator::initPWM(byte pin) {

    numLeds_ = 1;
    numPins_ = 1;

    pins_ = (byte*)malloc(1);
    pins_[0] = pin;

    pinMode(pin, OUTPUT);

    // allocate and clear leds array
    ledColors_ = (ESPectro_LED_Color *)malloc(3*numLeds_);
    memset(ledColors_, 0, 3*numLeds_);
}

void ESPectro_LED_Animator::setAnimation(ESPectro_LED_Animator::ESPectro_LED_AnimationType animType, uint32_t speed) {

    // is there any change?
    if (this->animationType_ == animType && this->speed_ == speed)
        return;

    animationType_ = animType;
    speed_ = speed;

    palette_.numColors = 1;
    palette_.colors = (ESPectro_LED_Color*)malloc(3);
    palette_.colors[0] = ESPectro_LED_Color(0xFFFFFF);

    setAnimationFunc(animationType_);
    animStartTime_ = millis();
}

void ESPectro_LED_Animator::setAnimationFunc(ESPectro_LED_Animator::ESPectro_LED_AnimationType animType) {
    switch(animType)
    {
        case ESPectro_LED_Animation_ON:                     animFunc_ = &ESPectro_LED_Animator::on;                    break;
        case ESPectro_LED_Animation_OFF:                    animFunc_ = &ESPectro_LED_Animator::off;                   break;
        case ESPectro_LED_Animation_Blink:                  animFunc_ = &ESPectro_LED_Animator::blink;                 break;
        case ESPectro_LED_Animation_Fading:                 animFunc_ = &ESPectro_LED_Animator::fade;                  break;
        case ESPectro_LED_Animation_Strobo:                 animFunc_ = &ESPectro_LED_Animator::strobo;                break;
        default:                                            animFunc_ = &ESPectro_LED_Animator::off;
    }
}

int ESPectro_LED_Animator::getStep(long t0, long t, int v)
{
    return ((millis()-t0)%t)*v/t;
}

float ESPectro_LED_Animator::getStepFloat(long t0, long t, float v)
{
    return ((millis()-t0)%t)*v/t;
}

bool ESPectro_LED_Animator::runAnimation() {

    // skip the refresh if not enough time has passed since last update
    unsigned long cTime = millis();
    if (cTime < lastRefreshTime_ + refreshMillis_)
        return false;

    // calculate real refresh rate
    refreshRate_ = 1000/(cTime - lastRefreshTime_);

    lastRefreshTime_ = cTime;

    if (animFunc_ != NULL)
    {
        (this->*animFunc_)();

        //PWM
        for(int i=0; i < numLeds_; i++)
        {
            int j = 3*i;

            if (numPins_ == 1) { //for 1 color LED
                analogWrite(pins_[0], (ledColors_[i].r * maxOut_.b) >> 8);
            }
            else {
                analogWrite(pins_[j], (ledColors_[i].r * maxOut_.r) >> 8);
                analogWrite(pins_[j + 1], (ledColors_[i].g * maxOut_.g) >> 8);
                analogWrite(pins_[j + 2], (ledColors_[i].b * maxOut_.b) >> 8);
            }
        }
    }

    return true;
}

void ESPectro_LED_Animator::setRefreshRate(int refreshRate) {
    this->refreshMillis_ = 1000/refreshRate;
}

void ESPectro_LED_Animator::on() {
    for(int i = 0; i < numLeds_; i++)
    {
        ledColors_[i] = palette_.colors[0];
    }
}

void ESPectro_LED_Animator::off() {
    for(int i = 0; i < numLeds_; i++)
    {
        ledColors_[i] = 0x000000;
    }
}

void ESPectro_LED_Animator::blink() {
    int t = getStep(animStartTime_, speed_, 2);
    int k = (t+1)%2;
    for(int x = 0; x < numLeds_; x++)
    {
        ledColors_[x] = palette_.colors[0].scale(k);
    }
}

void ESPectro_LED_Animator::fade() {
    float s = getStepFloat(animStartTime_, speed_, TWO_PI);
    float k = (-cos(s)+1)/2;

    for(int x=0; x < numLeds_; x++)
    {
        ledColors_[x] = palette_.colors[0].scale(k);
    }
}

void ESPectro_LED_Animator::strobo()
{
    int t = getStep(animStartTime_, speed_, 10);

    ESPectro_LED_Color c = palette_.colors[0].scale(t==0);
    for(int x=0; x < numLeds_; x++)
    {
        ledColors_[x] = c;
    }
}