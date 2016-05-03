//
//  Action.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Action.hpp"
#include "Node.hpp"

bool Action::init(){
    return true;
}
Action::~Action(){
    target = NULL;
};


void Action::setAnimationCurve(AnimationCurve curve) {
    m_animationCurve = curve;
}
AnimationCurve Action::getAnimationCurve() {
    return m_animationCurve;
}




Vec2 Action::currentVec2Value() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    float valX = 0.f;
    float valY = 0.f;
    switch (m_animationCurve) {
        case AnimationCurveLinear: {
            valX = animationFunctionLinear(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationFunctionLinear(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case AnimationCurveQuadraticEaseIn: {
            valX = animationFunctionQuadraticEaseIn(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationFunctionQuadraticEaseIn(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case AnimationCurveQuadraticEaseOut: {
            valX = animationFunctionQuadraticEaseOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationFunctionQuadraticEaseOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case AnimationCurveBounceEaseOut: {
            valX = bounceEaseOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = bounceEaseOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case AnimationCurveBounceEaseIn: {
            valX = bounceEaseIn(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = bounceEaseIn(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case AnimationCurveBounceEaseInOut: {
            valX = bounceEaseInOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = bounceEaseInOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        default: break;
    }
    return Vec2Make(valX,valY);
}
double Action::currentDoubleValue() {
    startVec2Value.x = startValue;
    changeInVec2Value.x = changeInValue;
    return currentVec2Value().x;
}