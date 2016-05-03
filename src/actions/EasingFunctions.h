//
//  EasingFunctions.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 03.05.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef EasingFunctions_hpp
#define EasingFunctions_hpp

#include <stdio.h>

enum EasingFunction {
    EasingFunctionLinear,
    EasingFunctionQuadraticEaseIn,
    EasingFunctionQuadraticEaseOut, // ?
    EasingFunctionQuadraticEaseInOut,
    
    EasingFunctionBounceEaseOut,
    EasingFunctionBounceEaseIn,
    EasingFunctionBounceEaseInOut,
    
    EasingFunctionBackEaseOut,
    EasingFunctionBackEaseIn,
    EasingFunctionBackEaseInOut,
};



/**
 * BounceEase- Out, In, InOut
 */
inline float animationBounceEaseOut(float t,float b , float c, float d) {
    if ((t/=d) < (1/2.75f)) {
        return c*(7.5625f*t*t) + b;
    } else if (t < (2/2.75f)) {
        float postFix = t-=(1.5f/2.75f);
        return c*(7.5625f*(postFix)*t + .75f) + b;
    } else if (t < (2.5/2.75)) {
        float postFix = t-=(2.25f/2.75f);
        return c*(7.5625f*(postFix)*t + .9375f) + b;
    } else {
        float postFix = t-=(2.625f/2.75f);
        return c*(7.5625f*(postFix)*t + .984375f) + b;
    }
}
inline float animationBounceEaseIn (float t,float b , float c, float d) {
    return c - animationBounceEaseOut(d-t, 0, c, d) + b;
}
inline float animationBounceEaseInOut(float t,float b , float c, float d) {
    if (t < d/2) return animationBounceEaseIn (t*2, 0, c, d) * .5f + b;
    else return animationBounceEaseOut (t*2-d, 0, c, d) * .5f + c*.5f + b;
}


/**
 * Back Out, In, InOut
 */
inline float backEaseIn (float t,float b , float c, float d) {
    float s = 1.70158f;
    float postFix = t/=d;
    return c*(postFix)*t*((s+1)*t - s) + b;
}
inline float backEeaseOut(float t,float b , float c, float d) {
    float s = 1.70158f;
    return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
}
inline float backEaseInOut(float t,float b , float c, float d) {
    float s = 1.70158f;
    if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
    float postFix = t-=2;
    return c/2*((postFix)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
}



/**
 * Linear
 */
inline float animationLinear(float time, float startValue, float changeInValue, float duration) {
    return changeInValue*time/duration + startValue;
}



inline float animationQuadEaseIn (float t,float b , float c, float d) {
    return c*(t/=d)*t + b;
}
inline float animationQuadEaseOut(float t,float b , float c, float d) {
    return -c *(t/=d)*(t-2) + b;
}

inline float animationQuadEaseInOut(float t,float b , float c, float d) {
    if ((t/=d/2) < 1) return ((c/2)*(t*t)) + b;
    return -c/2 * (((t-2)*(--t)) - 1) + b;
}

#endif /* EasingFunctions_hpp */
