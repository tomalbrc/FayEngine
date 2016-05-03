//
//  Action.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef Action_hpp
#define Action_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "Types.hpp"
#include "EasingFunctions.hpp"

enum AnimationCurve {
    AnimationCurveLinear,
    AnimationCurveQuadraticEaseIn,
    AnimationCurveQuadraticEaseOut,
    
    AnimationCurveBounceEaseOut,
    AnimationCurveBounceEaseIn,
    AnimationCurveBounceEaseInOut,
};
inline double animationFunctionLinear(double time, double startValue, double changeInValue, double duration) {
    return changeInValue*time/duration + startValue;
}
inline double animationFunctionQuadraticEaseIn(double time, double startValue, double changeInValue, double duration) {
    time /= duration;
    return changeInValue*time*time + startValue;
}
inline double animationFunctionQuadraticEaseOut(double time, double startValue, double changeInValue, double duration) {
    time /= duration;
    return -changeInValue * time*(time-2) + startValue;
}





class Node;
class Action;
FE_create_Ptr(Action);

/**
 * Actions to alter properties of Nodes/Sprites, animated
 */
class Action: public std::enable_shared_from_this<Action> { // abstract
public:
    /**
     * true if duration is over
     */
    bool finished = false;
    
    /**
     * Destructor
     */
    virtual ~Action();
    
    /**
     * Target Node of the Action
     */
    Node *target = NULL;
    
    /**
     * Duration of the Action in ms
     */
    double duration = 0;
    
    /**
     * update() gets called every frame
     */
    virtual void update() = 0;
    
    /**
     * start() will be called when assigning the Action no a Node
     */
    virtual void start() = 0;
    
    /**
     * Set an desired animation curve (function) for the action
     */
    void setAnimationCurve(AnimationCurve curve);

    /**
     * Returns the current set animation curve for the Action
     */
    AnimationCurve getAnimationCurve();
    
protected:
    bool init();
    Uint32 startTick;
    
    double startValue;
    double changeInValue;
    
    Vec2 startVec2Value;
    Vec2 changeInVec2Value;
    
    AnimationCurve m_animationCurve = AnimationCurveLinear; // Default value
    
    double currentDoubleValue();
    Vec2 currentVec2Value();
};


#endif /* Action_hpp */
