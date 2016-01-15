//
//  ScaleToAction.hpp
//  PixelDead_SDL
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
typedef std::unique_ptr<ScaleToAction> ScaleToActionPtr;

class Node;
class ScaleToAction : public Action {
    double mStartScale = 1.0;
    double mDestScale = 0.0;
public:
    ScaleToAction(double duration, double destScale);
    static ScaleToActionPtr create(double duration, double destScale);
    
    virtual void update();
    virtual void start();
};

#endif /* ScaleToAction_hpp */
