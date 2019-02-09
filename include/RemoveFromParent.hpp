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

#include "Action.hpp"
#include "Sprite.hpp"

RKT_NAMESPACE_BEGIN

class RemoveFromParentAction;
RKT_create_shared__ptr(RemoveFromParentAction);

/**
 * Removes the target Node from parent after a specified delay or immediately
 */
class RemoveFromParentAction : public Action {
public:
    static RemoveFromParentAction_ptr create();
    
    void update();
    void start();
private:
    bool init();
};

RKT_NAMESPACE_END
#endif /* RemoveFromParent_hpp */
