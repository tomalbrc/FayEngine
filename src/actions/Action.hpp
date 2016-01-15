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
#include <stdio.h>
#include <vector>
#include <iostream>
#include <memory>

class Node;
class Action;
typedef std::shared_ptr<Action> ActionPtr;

/**
 * Actions to alter properties of Nodes/Sprites
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
     * Duration of the Action
     */
    double duration = 0; // in ms
    
    /**
     * update() gets called every frame
     */
    virtual void update() = 0;
    
    /**
     * start() will be called when assigning the Action no a Node
     */
    virtual void start() = 0;
    
protected:
    bool init();
    Uint32 startTick;
};


#endif /* Action_hpp */
