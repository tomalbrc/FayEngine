//
//  EasingFunctions.cpp
//  rawket
//
//  Created by Tom Albrecht on 23.05.16.
//  
//

#include "EasingFunctions.hpp"
#include <math.h>

RKT_NAMESPACE_BEGIN

    
/**
 * BounceEase- Out, In, InOut
 */
float animationBounceEaseOut(float t,float b , float c, float d) {
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
float animationBounceEaseIn (float t,float b , float c, float d) {
    return c - animationBounceEaseOut(d-t, 0, c, d) + b;
}
float animationBounceEaseInOut(float t,float b , float c, float d) {
    if (t < d/2) return animationBounceEaseIn (t*2, 0, c, d) * .5f + b;
    else return animationBounceEaseOut (t*2-d, 0, c, d) * .5f + c*.5f + b;
}


/**
 * Back Out, In, InOut
 */
float animationBackEaseIn (float t,float b , float c, float d) {
    float s = 1.70158f;
    float postFix = t/=d;
    return c*(postFix)*t*((s+1)*t - s) + b;
}
float animationBackEaseOut(float t,float b , float c, float d) {
    t=t/d-1;
    float s = 1.70158f;
    return c*((t)*t*((s+1)*t + s) + 1) + b;
}
float animationBackEaseInOut(float t,float b , float c, float d) {
    float s = 1.70158f;
    (s*=(1.525f)); // TODO: Check for bugs
    if ((t/=d/2) < 1) return c/2*(t*t*((+1)*t - s)) + b;
    float postFix = t-=2;
    s*=(1.525f);
    return c/2*((postFix)*t*(((s)+1)*t + s) + 2) + b;
}



/**
 * Linear
 */
float animationLinear(float time, float startValue, float changeInValue, float duration) {
    //RKTLog("Linear percentage: "<<time/duration);
    return changeInValue*time/duration + startValue;
}



/**
 * Quad Ease In, Out, InOut
 */
float animationQuadEaseIn (float t,float b , float c, float d) {
    t /= d;
    return c*t*t + b;
}
float animationQuadEaseOut(float t,float b , float c, float d) {
    t /= d;
    return -c *t*(t-2) + b;
}

float animationQuadEaseInOut(float t,float b , float c, float d) {
    t /= d/2;
    if (t < 1) return c/2*t*t + b;
    t--;
    return -c/2 * (t*(t-2) - 1) + b;
}


/**
 * Elastic animation
 */
float animationElasticEaseIn (float t,float b , float c, float d) {
    if (t==0) return b;  if ((t/=d)==1) return b+c;
    float p=d*.3f;
    float a=c;
    float s=p/4;
    t--;
    float postFix =a*pow(2,10*t); // this is a fix, again, with post-increment operators
    return -(postFix * sin((t*d-s)*(2*M_PI)/p )) + b;
}
float animationElasticEaseOut(float t,float b , float c, float d) {
    if (t==0) return b;  if ((t/=d)==1) return b+c;
    float p=d*.3f;
    float a=c;
    float s=p/4;
    return (a*pow(2,-10*t) * sin( (t*d-s)*(2*M_PI)/p ) + c + b);
}
float animationElasticEaseInOut(float t,float b , float c, float d) {
    if (t==0) return b;  if ((t/=d/2)==2) return b+c;
    float p=d*(.3f*1.5f);
    float a=c;
    float s=p/4;
    
    if (t < 1) {
        float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
        return -.5f*(postFix* sin( (t*d-s)*(2*M_PI)/p )) + b;
    }
    float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
    return postFix * sin( (t*d-s)*(2*M_PI)/p )*.5f + c + b;
}


/**
 * Sine animation
 */
float animationSineEaseIn (float t,float b , float c, float d) {
    return -c * cos(t/d * (M_PI/2)) + c + b;
}
float animationSineEaseOut(float t,float b , float c, float d) {
    return c * sin(t/d * (M_PI/2)) + b;
}
float animationSineEaseInOut(float t,float b , float c, float d) {
    return -c/2 * (cos(M_PI*t/d) - 1) + b;
}


RKT_NAMESPACE_END
