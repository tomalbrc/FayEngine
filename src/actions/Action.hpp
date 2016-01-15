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
    bool finished = false;
    
    virtual ~Action();
    
    Node *target = NULL;
    double duration = 0; // in ms
    
    virtual void update() = 0;
    virtual void start() = 0;
    
protected:
    bool init();
    Uint32 startTick;
};


#endif /* Action_hpp */
