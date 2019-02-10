//
//  scale_to_action.hpp
//  rawket
//
//  Created by Tom Albrecht on 25.12.15.
//  
//

#ifndef ScaleToAction_hpp
#define ScaleToAction_hpp

#include <vector>
#include <iostream>
#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class scale_to_action;
rkt_create_shared_ptr(scale_to_action);

/**
 * Scales the target Nodes by x in y duration
 */
class scale_to_action : public action {
    vec2f m_scale = vec2f_make(1.0, 1.0);
public:
    scale_to_action(double duration, double destScale);
    static scale_to_action_ptr create(double duration, double destScale);
    
    virtual void update();
    virtual void start();
};

    
RKT_NAMESPACE_END
#endif /* ScaleToAction_hpp */
