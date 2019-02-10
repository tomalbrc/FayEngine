//
//  move_by_action.hpp
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

#include "action.hpp"
#include "node.hpp"

RKT_NAMESPACE_BEGIN

class move_by_action;
rkt_create_shared_ptr(move_by_action);

/**
 * Moves the target node by a specified distance in a specified duration
 */
class move_by_action : public action, public std::enable_shared_from_this<move_by_action> {
public:
    static move_by_action_ptr create(double duration, vec2f offset);
    
    void update();
    void start();
protected:
    bool init(double duration, vec2f offset);
};

RKT_NAMESPACE_END
#endif /* MoveByAction_hpp */
