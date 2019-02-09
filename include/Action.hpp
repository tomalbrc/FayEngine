//
//  Action.hpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#ifndef Action_hpp
#define Action_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "Types.hpp"
#include "EasingFunctions.hpp"

RKT_NAMESPACE_BEGIN

class Node;
class Action;
RKT_create__ptr(Action);

/**
 * Actions to alter properties of Nodes/Sprites, animated
 */
class Action { // abstract
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
     * Set an desired animation function for the action.
     * See EasingFunctions.h for Functions
     */
    void setEasingFunction(rkt::EasingFunction curve);

    /**
     * Returns the current set animation function for the Action
     */
    rkt::EasingFunction getEasingFunction();
    
protected:
    bool init();
    Uint32 startTick;
    
    double startValue = 0;
    double changeInValue = 0;
    
    Vec2 startVec2Value;
    Vec2 changeInVec2Value;
    
    rkt::EasingFunction m_animationCurve = rkt::EasingFunctionLinear; // Default value
    
    double currentDoubleValue();
    Vec2 currentVec2Value();
};

RKT_NAMESPACE_END
#endif /* Action_hpp */
