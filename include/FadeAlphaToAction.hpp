//
//  FadeAlphaToAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef FadeAlphaToAction_hpp
#define FadeAlphaToAction_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "tmxparser.h"
#include "Types.hpp"
#include "Action.hpp"
#include "Sprite.hpp"

FE_NAMESPACE_BEGIN

class FadeAlphaToAction;
FE_create_shared_Ptr(FadeAlphaToAction);

/**
 * Fades the alpha value of a Node to the desired value in a specified amount of time
 */
class FadeAlphaToAction : public Action {
    int m_alpha;
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
};

FE_NAMESPACE_END
#endif /* FadeAlphaToAction_hpp */
