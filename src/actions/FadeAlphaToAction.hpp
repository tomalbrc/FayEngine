//
//  FadeAlphaToAction.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef FadeAlphaToAction_hpp
#define FadeAlphaToAction_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "tmxparser.h"

#include "Action.hpp"
#include "Sprite.hpp"

class FadeAlphaToAction;
typedef std::unique_ptr<FadeAlphaToAction> FadeAlphaToActionPtr;
class Node;

/**
 * Fades the alpha value of a Node to the desired value in a specified amount of time
 */
class FadeAlphaToAction : public Action {
public:
    static FadeAlphaToActionPtr create(double duration, int destAlpha);
    
    /**
     * Re-implementation from base class Action
     */
    virtual void update();
    
    /**
     * Re-implementation from base class Action
     */
    virtual void start();
    
protected:
    bool init(double duration, int destAlpha);
private:
    int startAlpha = 255;
    int alphaValue = 0;
};

#endif /* FadeAlphaToAction_hpp */
