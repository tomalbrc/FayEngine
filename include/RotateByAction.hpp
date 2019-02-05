//
//  RotateByAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 19.02.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef RotateByAction_hpp
#define RotateByAction_hpp

#include <vector>
#include <iostream>
#include "Action.hpp"
#include "Sprite.hpp"

FE_NAMESPACE_BEGIN

class RotateByAction;
FE_create_shared_Ptr(RotateByAction);

/**
 * Rotates the target Nodes by x radians in y duration
 */
class RotateByAction : public Action {
public:
    RotateByAction(double duration, double radians);
    static RotateByActionPtr create(double duration, double radians);
    
    void update();
    void start();
};

FE_NAMESPACE_END
#endif /* RotateByAction_hpp */