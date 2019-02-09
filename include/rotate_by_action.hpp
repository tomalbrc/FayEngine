//
//  rotate_by_action.hpp
//  rawket
//
//  Created by Tom Albrecht on 19.02.16.
//  
//

#ifndef RotateByAction_hpp
#define RotateByAction_hpp

#include <vector>
#include <iostream>
#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class rotate_by_action;
RKT_create_shared__ptr(rotate_by_action);

/**
 * Rotates the target Nodes by x radians in y duration
 */
class rotate_by_action : public action {
public:
    rotate_by_action(double duration, double radians);
    static rotate_by_action_ptr create(double duration, double radians);
    
    void update();
    void start();
};

RKT_NAMESPACE_END
#endif /* RotateByAction_hpp */
