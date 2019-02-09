//
//  RotateToAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 25.12.15.
//  
//

#ifndef RotateToAction_hpp
#define RotateToAction_hpp

#include <vector>
#include <iostream>
#include "Action.hpp"
#include "Sprite.hpp"

RKT_NAMESPACE_BEGIN

class RotateToAction;
RKT_create_shared__ptr(RotateToAction);

/**
 * Rotates the target Nodes to x radians in y duration
 */
class RotateToAction : public Action {
    float m_radians;
public:
    RotateToAction(double duration, float radians);
    static RotateToAction_ptr create(double duration, float radians);
    
    void update();
    void start();
};

RKT_NAMESPACE_END
#endif /* RotateToAction_hpp */
