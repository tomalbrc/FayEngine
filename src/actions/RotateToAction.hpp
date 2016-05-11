//
//  RotateToAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 25.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef RotateToAction_hpp
#define RotateToAction_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#include "Action.hpp"
#include "Sprite.hpp"

class RotateToAction;
FE_create_shared_Ptr(RotateToAction);

/**
 * Rotates the target Nodes to x radians in y duration
 */
class RotateToAction : public Action {
    float m_radians;
public:
    RotateToAction(double duration, float radians);
    static RotateToActionPtr create(double duration, float radians);
    
    void update();
    void start();
};

#endif /* RotateToAction_hpp */
