//
//  RotateByAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 19.02.16.
//  
//

#ifndef RotateByAction_hpp
#define RotateByAction_hpp

#include <vector>
#include <iostream>
#include "Action.hpp"
#include "Sprite.hpp"

RKT_NAMESPACE_BEGIN

class RotateByAction;
RKT_create_shared__ptr(RotateByAction);

/**
 * Rotates the target Nodes by x radians in y duration
 */
class RotateByAction : public Action {
public:
    RotateByAction(double duration, double radians);
    static RotateByAction_ptr create(double duration, double radians);
    
    void update();
    void start();
};

RKT_NAMESPACE_END
#endif /* RotateByAction_hpp */
