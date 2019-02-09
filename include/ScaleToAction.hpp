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

FE_NAMESPACE_BEGIN

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

    
FE_NAMESPACE_END
#endif /* ScaleToAction_hpp */
