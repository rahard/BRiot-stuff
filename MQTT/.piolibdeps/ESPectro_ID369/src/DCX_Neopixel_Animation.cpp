//
// Created by Andri Yadi on 9/1/16.
//

#include "DCX_Neopixel_Animation.h"

DCX_Neopixel_Animation::DCX_Neopixel_Animation(ESPectro_Neopixel_Default &neopixel):neopixel_(neopixel) {

}

DCX_Neopixel_Animation::~DCX_Neopixel_Animation() {
    if (animator_ != NULL) {
        delete animator_;
        animator_ = NULL;
    }
}

void DCX_Neopixel_Animation::start() {

    if (neopixel_.PixelCount() == 0) {
        return;
    }

    if (animator_ == NULL) {
        animator_ = new NeoPixelAnimator(neopixel_.PixelCount(), NEO_MILLISECONDS);
    }

    animationPrevStarted_ = true;
}

void DCX_Neopixel_Animation::end() {
    animationPrevStarted_ = false;
}

void DCX_Neopixel_Animation::run() {
    if (animator_ != NULL) {
        if (animator_->IsAnimating()) {
            animator_->UpdateAnimations();
            neopixel_.Show();
        }
//        else {
//            Serial.print("X");
//            if (animationPrevStarted_) {
//                if (animCompletedCb_) {
//                    animCompletedCb_();
//                }
//            }
//        }

        if (animationPrevStarted_ && !animator_->IsAnimationActive(0)) {
            end();
            if (animCompletedCb_) {
                animCompletedCb_();
            }
        }
    }
}

void DCX_Neopixel_Animation::onAnimationCompleted(AnimationCompletedCallback cb) {
    animCompletedCb_ = cb;
}



DCX_Neopixel_PulseAnimation::DCX_Neopixel_PulseAnimation(ESPectro_Neopixel_Default &neopixel, RgbColor &toColor): DCX_Neopixel_Animation(neopixel), pulsingToColor_(toColor) {

}

DCX_Neopixel_PulseAnimation::~DCX_Neopixel_PulseAnimation() {

}

void DCX_Neopixel_PulseAnimation::start() {

    DCX_Neopixel_Animation::start();

    if (animator_->IsAnimating()) {
        animator_->StopAnimation(0);
    }

    AnimEaseFunction easing = NeoEase::Linear;

    RgbColor original = neopixel_.GetPixelColor(0);
    RgbColor target = (pulsingAnimationState_ == 0)? RgbColor(pulsingToColor_): RgbColor(0);

    //strip.SetPixelColor(i, color);

    DCX_Neopixel_PulseAnimation *mySelf = this;

    AnimUpdateCallback animUpdate = [=](const AnimationParam& param)
    {
        // progress will start at 0.0 and end at 1.0
        // we convert to the curve we want
        float progress = easing(param.progress);

        // use the curve value to apply to the animation
        RgbColor updatedColor = RgbColor::LinearBlend(original, target, progress);

        for(uint16_t i = 0; i < mySelf->neopixel_.PixelCount(); i++) {
            mySelf->neopixel_.SetPixelColor(i, updatedColor);
        }

        if (progress >= 0.9999) {
            //Serial.println("Animation DONE");

            //Repeat
            mySelf->start();
        }
    };

    animator_->StartAnimation(0, pulsingInterval_, animUpdate);
    pulsingAnimationState_ = (pulsingAnimationState_ + 1) % 2;
}

void DCX_Neopixel_PulseAnimation::end() {

    if (animator_ == NULL) {
        return;
    }

    DCX_Neopixel_Animation::end();

    for(uint16_t i = 0; i < neopixel_.PixelCount(); i++) {
        neopixel_.SetPixelColor(i, RgbColor(0));
    }
    neopixel_.Show();

    if (animator_ != NULL) {
        if (animator_->IsAnimating()) {
            animator_->StopAnimation(0);
        }

        delete animator_;
        animator_ = NULL;
    }
}

void DCX_Neopixel_PulseAnimation::setPulsingToColor(RgbColor &toColor) {
    pulsingToColor_ = toColor;
}

void DCX_Neopixel_PulseAnimation::setPulsingInterval(uint16_t pulsingInterval) {
    pulsingInterval_ = pulsingInterval;
}

//------

DCX_Neopixel_CyclonAnimation::DCX_Neopixel_CyclonAnimation(ESPectro_Neopixel_Default &neopixel):
        DCX_Neopixel_Animation(neopixel) {

}

DCX_Neopixel_CyclonAnimation::~DCX_Neopixel_CyclonAnimation() {
//    if (animator_ != NULL) {
//        delete animator_;
//        animator_ = NULL;
//    }
}

//const RgbColor CylonEyeColor(HtmlColor(0x7f0000));

void DCX_Neopixel_CyclonAnimation::fadeAll(uint8_t darkenBy)
{
    RgbColor color;
    for (uint16_t indexPixel = 0; indexPixel < neopixel_.PixelCount(); indexPixel++)
    {
        color = neopixel_.GetPixelColor(indexPixel);
        color.Darken(darkenBy);
        neopixel_.SetPixelColor(indexPixel, color);
    }
}

void DCX_Neopixel_CyclonAnimation::start() {

    if (neopixel_.PixelCount() == 0) {
        return;
    }

    if (animator_ == NULL) {
        animator_ = new NeoPixelAnimator(2);
    }

    animationPrevStarted_ = true;

    AnimEaseFunction moveEase =
//      NeoEase::Linear;
//      NeoEase::QuadraticInOut;
//      NeoEase::CubicInOut;
            NeoEase::QuarticInOut;
//      NeoEase::QuinticInOut;
//      NeoEase::SinusoidalInOut;
//      NeoEase::ExponentialInOut;
//      NeoEase::CircularInOut;

    uint16_t PixelCount = neopixel_.PixelCount();
    DCX_Neopixel_CyclonAnimation *mySelf = this;

    AnimUpdateCallback moveAnimUpdate = [=](const AnimationParam& param)
    {
        // apply the movement animation curve
        float progress = moveEase(param.progress);

        // use the curved progress to calculate the pixel to effect
        uint16_t nextPixel;
        if (mySelf->moveDir_ > 0)
        {
            nextPixel = progress * PixelCount;
        }
        else
        {
            nextPixel = (1.0f - progress) * PixelCount;
        }

        // if progress moves fast enough, we may move more than
        // one pixel, so we update all between the calculated and
        // the last
        if (mySelf->lastPixel_ != nextPixel)
        {
            for (uint16_t i = mySelf->lastPixel_ + mySelf->moveDir_; i != nextPixel; i += mySelf->moveDir_)
            {
                mySelf->setPixelColor(i);
            }
        }
        mySelf->setPixelColor(nextPixel);

        mySelf->lastPixel_ = nextPixel;

        if (param.state == AnimationState_Completed)
        {
            // reverse direction of movement
            mySelf->moveDir_ *= -1;

            // done, time to restart this position tracking animation/timer
            mySelf->animator_->RestartAnimation(param.index);

            // mySelf->animator_->StopAnimation(0);
        }
    };



    AnimUpdateCallback fadeAnimUpdate = [=](const AnimationParam& param)
    {
        if (param.state == AnimationState_Completed)
        {
            mySelf->fadeAll(10);
            mySelf->animator_->RestartAnimation(param.index);
        }
    };

    animator_->StartAnimation(0, 5, fadeAnimUpdate);

    // take several seconds to move eye fron one side to the other
    animator_->StartAnimation(1, 1000, moveAnimUpdate);
}

void DCX_Neopixel_CyclonAnimation::end() {

    DCX_Neopixel_Animation::end();

    animator_->StopAnimation(0);
    animator_->StopAnimation(1);

//    animationPrevStarted_ = false;
}

//void DCX_Neopixel_CyclonAnimation::run() {
//
//    if (animator_ != NULL) {
//        if (animator_->IsAnimating()) {
//            animator_->UpdateAnimations();
//            neopixel_.Show();
//        }
////        else {
////            Serial.print("X");
////            if (animationPrevStarted_) {
////                if (animCompletedCb_) {
////                    animCompletedCb_();
////                }
////            }
////        }
//
//        if (animationPrevStarted_ && !animator_->IsAnimationActive(0)) {
//            end();
//            if (animCompletedCb_) {
//                animCompletedCb_();
//            }
//        }
//    }
//}

void DCX_Neopixel_CyclonAnimation::setPixelColor(uint16_t idx) {
    //neopixel_.SetPixelColor(idx, CylonEyeColor);

    float hue = 360.0f - ((idx*1.0f/neopixel_.PixelCount())*270);

    HslColor color = HslColor(hue/360.0f, 1.0f, 0.5f);
    neopixel_.SetPixelColor(idx, color);
}

//void DCX_Neopixel_CyclonAnimation::onAnimationCompleted(AnimationCompletedCallback cb) {
//    animCompletedCb_ = cb;
//}

void DCX_Neopixel_CyclonAnimation::setAnimationDirection(bool up) {
    if (up) {
        moveDir_ = 1;
    }
    else {
        moveDir_ = -1;
    }
}


