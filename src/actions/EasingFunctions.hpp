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
#include "Types.hpp"

FE_NAMESPACE_BEGIN

enum EasingFunction {
    EasingFunctionLinear,
    
    EasingFunctionQuadEaseIn,
    EasingFunctionQuadEaseOut,
    EasingFunctionQuadEaseInOut,
    
    EasingFunctionBounceEaseOut,
    EasingFunctionBounceEaseIn,
    EasingFunctionBounceEaseInOut,
    
    EasingFunctionBackEaseOut,
    EasingFunctionBackEaseIn,
    EasingFunctionBackEaseInOut,
    
    EasingFunctionElasticEaseOut,
    EasingFunctionElasticEaseIn,
    EasingFunctionElasticEaseInOut,
    
    EasingFunctionSineEaseOut,
    EasingFunctionSineEaseIn,
    EasingFunctionSineEaseInOut,
};


/**
 * BounceEase- Out, In, InOut
 */
extern float animationBounceEaseOut(float t,float b , float c, float d);
extern float animationBounceEaseIn (float t,float b , float c, float d);
extern float animationBounceEaseInOut(float t,float b , float c, float d);

/**
 * Back Out, In, InOut
 */
extern float animationBackEaseIn (float t,float b , float c, float d);
extern float animationBackEaseOut(float t,float b , float c, float d);
extern float animationBackEaseInOut(float t,float b , float c, float d);

/**
 * Linear
 */
extern float animationLinear(float time, float startValue, float changeInValue, float duration);

/**
 * Quad Ease In, Out, InOut
 */
extern float animationQuadEaseIn (float t,float b , float c, float d);
extern float animationQuadEaseOut(float t,float b , float c, float d);
extern float animationQuadEaseInOut(float t,float b , float c, float d);

/**
 * Elastic animation
 */
extern float animationElasticEaseIn (float t,float b , float c, float d);
extern float animationElasticEaseOut(float t,float b , float c, float d);
extern float animationElasticEaseInOut(float t,float b , float c, float d);

/**
 * Sine animation
 */
extern float animationSineEaseIn (float t,float b , float c, float d);
extern float animationSineEaseOut(float t,float b , float c, float d);
extern float animationSineEaseInOut(float t,float b , float c, float d);

FE_NAMESPACE_END
#endif /* EasingFunctions_hpp */
