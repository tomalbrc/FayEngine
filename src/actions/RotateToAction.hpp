//
//  RotateToAction.hpp
//  PixelDead_SDL
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
typedef std::unique_ptr<RotateToAction> RotateToActionPtr;
class Node;

/**
 * Rotates the target Nodes to x radians in y duration
 */
class RotateToAction : public Action {
public:
    RotateToAction(double duration, double radians);
    static RotateToActionPtr create(double duration, double radians);

    
    void update();
    void start();
    
    
private:
    double mDestRot = 255;
    double mStartRot = 0;
};

#endif /* RotateToAction_hpp */
