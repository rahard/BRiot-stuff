//
// Created by Andri Yadi on 3/17/17.
//

#ifndef ESPECTROCORE_ESPECTRO_LED_H
#define ESPECTROCORE_ESPECTRO_LED_H


#include <Arduino.h>
#include "ESPectro_Constants.h"
#include <Ticker.h>
#include <functional>
//#include <exception>

#define min(a,b) ((a)<(b)?(a):(b))

struct ESPectro_LED_Color
{
    union
    {
        struct
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;
        };
        uint8_t raw[3];
    };

    inline ESPectro_LED_Color() __attribute__((always_inline))
    {
    }

    // allow construction from R, G, B
    inline ESPectro_LED_Color( uint8_t ir, uint8_t ig, uint8_t ib)  __attribute__((always_inline))
            : r(ir), g(ig), b(ib)
    {
    }

    // allow construction from 32-bit (really 24-bit) bit 0xRRGGBB color code
    inline ESPectro_LED_Color( uint32_t colorcode)  __attribute__((always_inline))
            : r((colorcode >> 16) & 0xFF), g((colorcode >> 8) & 0xFF), b((colorcode >> 0) & 0xFF)
    {
    }

    bool operator == (const ESPectro_LED_Color &c) const
    {
        return(this->r == c.r and this->g == c.g and this->b == c.b);
    }
/*
    ESPectro_LED_Color getPixel(AlaColor maxOut)
    {
        return ESPectro_LED_Color(r*maxOut.r/255, g*maxOut.g/255, b*maxOut.b/255);
    }
*/
    ESPectro_LED_Color sum(ESPectro_LED_Color color)
    {
        int r0 = min(color.r + r, 255);
        int g0 = min(color.g + g, 255);
        int b0 = min(color.b + b, 255);
        return ESPectro_LED_Color(r0, g0, b0);
    }

    ESPectro_LED_Color interpolate(ESPectro_LED_Color color, float x)
    {
        int r0 = x*(color.r - r) + r;
        int g0 = x*(color.g - g) + g;
        int b0 = x*(color.b - b) + b;
        return ESPectro_LED_Color(r0, g0, b0);
    }

    ESPectro_LED_Color scale(float k)
    {
        int r0 = min(r*k, 255);
        int g0 = min(g*k, 255);
        int b0 = min(b*k, 255);
        return ESPectro_LED_Color(r0, g0, b0);
    }
};

struct ESPectro_LED_Palette
{
    int numColors;
    ESPectro_LED_Color *colors;

    /**
    * Get the interpolated color from the palette.
    * The argument is a floating number between 0 and numColors.
    */
    ESPectro_LED_Color getPalColor(float i)
    {
        int i0 = (int)i%(numColors);
        int i1 = (int)(i+1)%(numColors);

        // decimal part is used to interpolate between the two colors
        float t0 = i - trunc(i);
        //float t0 = i - (int)i;

        return colors[i0].interpolate(colors[i1], t0);
    }

    bool operator == (const ESPectro_LED_Palette &c) const
    {
        if (!(this->numColors == c.numColors))
            return false;

        for(int i=0; i<numColors; i++)
        {
            if (!(this->colors[i] == c.colors[i]))
                return false;
        }
        return true;
    }
};

class ESPectro_LED_Animator {
public:

    enum ESPectro_LED_AnimationType {
        ESPectro_LED_Animation_ON,
        ESPectro_LED_Animation_OFF,
        ESPectro_LED_Animation_Blink,
        ESPectro_LED_Animation_Fading,
        ESPectro_LED_Animation_Strobo
    };

    ESPectro_LED_Animator();
    ~ESPectro_LED_Animator();

    void initPWM(byte pin);
    void setAnimation(ESPectro_LED_AnimationType animType, uint32_t speed);
    bool runAnimation();

    void setBrightness(ESPectro_LED_Color maxOut)
    {
        this->maxOut_ = maxOut;
    }

    /**
	* Sets the maximum refresh rate in Hz (default value is 50 Hz).
	* May be useful to reduce flickering in some cases.
	*/
    void setRefreshRate(int refreshRate);

private:
    ESPectro_LED_AnimationType animationType_;
    uint32_t speed_;
    uint32_t refreshMillis_;
    uint32_t refreshRate_;   // current refresh rate
    unsigned long animStartTime_, lastRefreshTime_;

    byte *pins_;     // pins where the leds are attached to
    byte numLeds_, numPins_;
    ESPectro_LED_Color maxOut_;
    ESPectro_LED_Color *ledColors_; // array to store leds brightness values
    ESPectro_LED_Palette palette_;

    void (ESPectro_LED_Animator::*animFunc_)();
    void setAnimationFunc(ESPectro_LED_AnimationType animType);

    int getStep(long t0, long t, int v);
    float getStepFloat(long t0, long t, float v);

    void on();
    void off();
    void blink();
    void fade();
    void strobo();
};

class ESPectro_LED {
public:

    ESPectro_LED(byte pin = ESPECTRO_LED_PIN, boolean activeHigh = true);
    ~ESPectro_LED();

    void begin();
    void turnOn();
    void turnOff();
    boolean isOn();
    byte getPin();
    void toggle();

    void blink(uint32_t interval = 500, uint32_t count = UINT16_MAX);
    void fade(uint32_t duration = 2000, uint32_t count = UINT16_MAX);

    void startAnimation();
    void stopAnimation();
    bool isAnimating() const;
    void setAnimation(ESPectro_LED_Animator::ESPectro_LED_AnimationType animType, uint32_t speed, uint32_t count = UINT16_MAX);
    void setAnimationTimeout(unsigned long timeOut);
    void updateAnimation();

private:
    byte pin_;
    boolean activeHigh_;

    Ticker *animTicker_ = NULL;
    ESPectro_LED_Animator *animator_ = NULL;
    unsigned long animationTimeOut_ = 30000;
    unsigned long startAnimationTime_ = 0;
    bool animating_ = false;
};


#endif //ESPECTROCORE_ESPECTRO_LED_H
