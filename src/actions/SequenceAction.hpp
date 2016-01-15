//
//  SequenceAction.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 22.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef SequenceAction_hpp
#define SequenceAction_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#include "Action.hpp"
#include "Sprite.hpp"

class SequenceAction;
typedef std::unique_ptr<SequenceAction> SequenceActionPtr;
class Node;

/**
 * Performs a sequence of actions, one-by-one
 */
class SequenceAction : public Action {
public:
    static SequenceActionPtr create(std::vector<ActionPtr> actions);
    ~SequenceAction();
    
    void update();
    void start();
    
    
protected:
    bool init(std::vector<ActionPtr> actions);
private:
    std::vector<ActionPtr> mActions;
    int currentIndex = 0;
    void prepareCurrentAction();
};

#endif /* SequenceAction_hpp */
