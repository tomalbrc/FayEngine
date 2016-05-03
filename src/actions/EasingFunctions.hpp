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

/**
 * BounceEase- Out, In, InOut
 */
inline float bounceEaseOut(float t,float b , float c, float d) {
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
inline float bounceEaseIn (float t,float b , float c, float d) {
    return c - bounceEaseOut(d-t, 0, c, d) + b;
}
inline float bounceEaseInOut(float t,float b , float c, float d) {
    if (t < d/2) return bounceEaseIn (t*2, 0, c, d) * .5f + b;
    else return bounceEaseOut (t*2-d, 0, c, d) * .5f + c*.5f + b;
}


#endif /* EasingFunctions_hpp */
