//
//  RemoveFromParent.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 10.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef RemoveFromParent_hpp
#define RemoveFromParent_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#include "Action.hpp"
#include "Sprite.hpp"

class RemoveFromParentAction;
typedef std::unique_ptr<RemoveFromParentAction> RemoveFromParentActionPtr;
class Node;

/**
 * Removes the target Node from parent after a specified delay or immediately
 */
class RemoveFromParentAction : public Action {
public:
    static RemoveFromParentActionPtr create();
    static RemoveFromParentActionPtr create(double delay);
    
    void update();
    void start();
    
    
private:
    bool init();
    bool init(double delay);
};

#endif /* RemoveFromParent_hpp */
