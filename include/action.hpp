//
//  action.hpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#ifndef Action_hpp
#define Action_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "types.hpp"
#include "easing_function.hpp"

RKT_NAMESPACE_BEGIN

class node;
class action;
RKT_create_ptr(action);

/**
 * Actions to alter properties of Nodes/Sprites, animated
 */
class action { // abstract
public:
    /**
     * true if duration is over
     */
    bool finished = false;
    
    /**
     * Destructor
     */
    virtual ~action();
    
    /**
     * Target node of the action
     */
    node *target = NULL;
    
    /**
     * Duration of the action in ms
     */
    double duration = 0;
    
    /**
     * update() gets called every frame
     */
    virtual void update() = 0;
    
    /**
     * start() will be called when assigning the action no a node
     */
    virtual void start() = 0;
    
    /**
     * Set an desired animation function for the action.
     * See easing_function.h for Functions
     */
    void setEasingFunction(rkt::EasingFunction curve);

    /**
     * Returns the current set animation function for the action
     */
    rkt::EasingFunction getEasingFunction();
    
protected:
    bool init();
    Uint32 startTick;
    
    double startValue = 0;
    double changeInValue = 0;
    
    vec2f startVec2Value;
    vec2f changeInVec2Value;
    
    rkt::EasingFunction m_animationCurve = rkt::EasingFunctionLinear; // Default value
    
    double currentDoubleValue();
    vec2f currentVec2Value();
};

RKT_NAMESPACE_END
#endif /* Action_hpp */
