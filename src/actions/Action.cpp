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


void Action::setEasingFunction(EasingFunction curve) {
    m_animationCurve = curve;
}
EasingFunction Action::getEasingFunction() {
    return m_animationCurve;
}




Vec2 Action::currentVec2Value() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    float valX = 0.f;
    float valY = 0.f;
    switch (m_animationCurve) {
        case EasingFunctionLinear: {
            valX = animationLinear(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationLinear(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
            
            
        case EasingFunctionQuadraticEaseIn: {
            valX = animationQuadEaseIn(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationQuadEaseIn(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionQuadraticEaseOut: {
            valX = animationQuadEaseOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationQuadEaseOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionQuadraticEaseInOut: {
            valX = animationQuadEaseInOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationQuadEaseInOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
         
            
        case EasingFunctionBounceEaseOut: {
            valX = animationBounceEaseOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationBounceEaseOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionBounceEaseIn: {
            valX = animationBounceEaseIn(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationBounceEaseIn(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionBounceEaseInOut: {
            valX = animationBounceEaseInOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationBounceEaseInOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
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