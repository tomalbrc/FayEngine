//
//  RemoveFromParent.hpp
//  rawket
//
//  Created by Tom Albrecht on 10.12.15.
//  
//

#ifndef RemoveFromParent_hpp
#define RemoveFromParent_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class remove_action;
rkt_create_shared_ptr(remove_action);

/**
 * Removes the target node from parent after a specified delay or immediately
 */
class remove_action : public action {
public:
    static remove_action_ptr create();
    
    void update();
    void start();
private:
    bool init();
};

RKT_NAMESPACE_END
#endif /* RemoveFromParent_hpp */
