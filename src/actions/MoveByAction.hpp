//
//  MoveByAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef MoveByAction_hpp
#define MoveByAction_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "tmxparser.h"

#include "Action.hpp"
#include "Node.hpp"

FE_NAMESPACE_BEGIN

class MoveByAction;
FE_create_shared_Ptr(MoveByAction);

/**
 * Moves the target Node by a specified distance in a specified duration
 */
class MoveByAction : public Action, public std::enable_shared_from_this<MoveByAction> {
public:
    static MoveByActionPtr create(double duration, Vec2 offset);
    
    void update();
    void start();
protected:
    bool init(double duration, Vec2 offset);
};

FE_NAMESPACE_END
#endif /* MoveByAction_hpp */
