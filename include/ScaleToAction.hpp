//
//  ScaleToAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 25.12.15.
//  
//

#ifndef ScaleToAction_hpp
#define ScaleToAction_hpp

#include <vector>
#include <iostream>
#include "Action.hpp"
#include "Sprite.hpp"

RKT_NAMESPACE_BEGIN

class ScaleToAction;
RKT_create_shared__ptr(ScaleToAction);

/**
 * Scales the target Nodes by x in y duration
 */
class ScaleToAction : public Action {
    Vec2 m_scale = Vec2Make(1.0, 1.0);
public:
    ScaleToAction(double duration, double destScale);
    static ScaleToAction_ptr create(double duration, double destScale);
    
    virtual void update();
    virtual void start();
};

    
RKT_NAMESPACE_END
#endif /* ScaleToAction_hpp */
