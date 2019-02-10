//
//  fade_action.hpp
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
#include "types.hpp"
#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class fade_action;
rkt_create_shared_ptr(fade_action);

/**
 * Fades the alpha value of a node to the desired value in a specified amount of time
 */
class fade_action : public action {
    int m_alpha;
public:
    static fade_action_ptr create(double duration, int destAlpha);
    
    /**
     * Re-implementation from base class action
     */
    virtual void update();
    
    /**
     * Re-implementation from base class action
     */
    virtual void start();
    
protected:
    bool init(double duration, int destAlpha);
};

RKT_NAMESPACE_END
#endif /* FadeAlphaToAction_hpp */
