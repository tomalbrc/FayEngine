//
//  rotate_to_action.hpp
//  rawket
//
//  Created by Tom Albrecht on 25.12.15.
//  
//

#ifndef RotateToAction_hpp
#define RotateToAction_hpp

#include <vector>
#include <iostream>
#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class rotate_to_action;
RKT_create_shared__ptr(rotate_to_action);

/**
 * Rotates the target Nodes to x radians in y duration
 */
class rotate_to_action : public action {
public:
    rotate_to_action(double duration, float radians);
    static rotate_to_action_ptr create(double duration, float radians);
    
    void update();
    void start();
};

RKT_NAMESPACE_END
#endif /* RotateToAction_hpp */
