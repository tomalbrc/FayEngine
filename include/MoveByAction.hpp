//
//  MoveByAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
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

RKT_NAMESPACE_BEGIN

class MoveByAction;
RKT_create_shared__ptr(MoveByAction);

/**
 * Moves the target Node by a specified distance in a specified duration
 */
class MoveByAction : public Action, public std::enable_shared_from_this<MoveByAction> {
public:
    static MoveByAction_ptr create(double duration, Vec2 offset);
    
    void update();
    void start();
protected:
    bool init(double duration, Vec2 offset);
};

RKT_NAMESPACE_END
#endif /* MoveByAction_hpp */
