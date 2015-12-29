//
//  MoveByAction.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef MoveByAction_hpp
#define MoveByAction_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "tmxparser.h"

#include "Action.hpp"
#include "Node.hpp"

class MoveByAction;
typedef std::unique_ptr<MoveByAction> MoveByActionPtr;

class Node;
class MoveByAction : public Action {
public:
    static MoveByActionPtr create(double duration, Vec2 offset);
    
    void update();
    void start();
    
protected:
    bool init(double duration, Vec2 offset);
private:
    Vec2 targetStartPos = Vec2Make(0,0);
    Vec2 moveValue = Vec2Make(0,0);
};

#endif /* MoveByAction_hpp */
