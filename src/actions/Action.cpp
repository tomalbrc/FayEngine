//
//  Action.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#include "Action.hpp"
#include "Node.hpp"

FE_NAMESPACE_BEGIN

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
    return Vec2Make(valX,valY);
}
double Action::currentDoubleValue() {
    startVec2Value.x = startValue;
    changeInVec2Value.x = changeInValue;
    return currentVec2Value().x;
}



FE_NAMESPACE_END
