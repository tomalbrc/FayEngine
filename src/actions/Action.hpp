//
//  Action.hpp
//  FayEngine
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

FE_NAMESPACE_BEGIN

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
     * Set an desired animation function for the action.
     * See EasingFunctions.h for Functions
     */
    void setEasingFunction(FE::EasingFunction curve);

    /**
     * Returns the current set animation function for the Action
     */
    FE::EasingFunction getEasingFunction();
    
protected:
    bool init();
    Uint32 startTick;
    
    double startValue;
    double changeInValue;
    
    Vec2 startVec2Value;
    Vec2 changeInVec2Value;
    
    FE::EasingFunction m_animationCurve = FE::EasingFunctionLinear; // Default value
    
    double currentDoubleValue();
    Vec2 currentVec2Value();
};

} // namespace FE
#endif /* Action_hpp */
