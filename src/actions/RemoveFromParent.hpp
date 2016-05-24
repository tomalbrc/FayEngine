//
//  RemoveFromParent.hpp
//  FayEngine
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

FE_NAMESPACE_BEGIN

class RemoveFromParentAction;
FE_create_shared_Ptr(RemoveFromParentAction);

/**
 * Removes the target Node from parent after a specified delay or immediately
 */
class RemoveFromParentAction : public Action {
public:
    static RemoveFromParentActionPtr create();
    
    void update();
    void start();
private:
    bool init();
};

} // namespace FE
#endif /* RemoveFromParent_hpp */
