//
//  FadeAlphaToAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#ifndef FadeAlphaToAction_hpp
#define FadeAlphaToAction_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "tmxparser.h"
#include "Types.hpp"
#include "Action.hpp"
#include "Sprite.hpp"

RKT_NAMESPACE_BEGIN

class FadeAlphaToAction;
RKT_create_shared__ptr(FadeAlphaToAction);

/**
 * Fades the alpha value of a Node to the desired value in a specified amount of time
 */
class FadeAlphaToAction : public Action {
    int m_alpha;
public:
    static FadeAlphaToAction_ptr create(double duration, int destAlpha);
    
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

RKT_NAMESPACE_END
#endif /* FadeAlphaToAction_hpp */
