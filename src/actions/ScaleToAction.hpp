//
//  ScaleToAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 25.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef ScaleToAction_hpp
#define ScaleToAction_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "tmxparser.h"

#include "Action.hpp"
#include "Sprite.hpp"

class ScaleToAction;
FE_create_shared_Ptr(ScaleToAction);

/**
 * Scales the target Nodes by x in y duration
 */
class ScaleToAction : public Action {
    Vec2 m_scale = Vec2Make(1.0, 1.0);
public:
    ScaleToAction(double duration, double destScale);
    static ScaleToActionPtr create(double duration, double destScale);
    
    virtual void update();
    virtual void start();
};

#endif /* ScaleToAction_hpp */
