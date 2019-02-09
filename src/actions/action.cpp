//
//  action.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#include "action.hpp"
#include "node.hpp"

RKT_NAMESPACE_BEGIN

bool action::init(){
    return true;
}
action::~action(){
    target = NULL;
};


void action::setEasingFunction(EasingFunction curve) {
    m_animationCurve = curve;
}
EasingFunction action::getEasingFunction() {
    return m_animationCurve;
}




vec2f action::currentVec2Value() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    float valX = 0.f;
    float valY = 0.f;
    switch (m_animationCurve) {
        case EasingFunctionLinear: {
            valX = animationLinear(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationLinear(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
            
            
        case EasingFunctionQuadEaseIn: {
            valX = animationQuadEaseIn(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationQuadEaseIn(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionQuadEaseOut: {
            valX = animationQuadEaseOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationQuadEaseOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionQuadEaseInOut: {
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
        
        
        
        case EasingFunctionBackEaseOut: {
            valX = animationBackEaseOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationBackEaseOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionBackEaseIn: {
            valX = animationBackEaseIn(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationBackEaseIn(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionBackEaseInOut: {
            valX = animationBackEaseInOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationBackEaseInOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        
        
        
        case EasingFunctionElasticEaseOut: {
            valX = animationElasticEaseOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationElasticEaseOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionElasticEaseIn: {
            valX = animationElasticEaseIn(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationElasticEaseIn(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionElasticEaseInOut: {
            valX = animationElasticEaseInOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationElasticEaseInOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
            
            
        case EasingFunctionSineEaseOut: {
            valX = animationSineEaseOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationSineEaseOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionSineEaseIn: {
            valX = animationSineEaseIn(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationSineEaseIn(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        case EasingFunctionSineEaseInOut: {
            valX = animationSineEaseInOut(passedTime, startVec2Value.x, changeInVec2Value.x, duration);
            valY = animationSineEaseInOut(passedTime, startVec2Value.y, changeInVec2Value.y, duration);
            break;
        }
        
        
            
        default: break;
    }
    return vec2f_make(valX,valY);
}
double action::currentDoubleValue() {
    startVec2Value.x = startValue;
    changeInVec2Value.x = changeInValue;
    return currentVec2Value().x;
}



RKT_NAMESPACE_END
