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

FE_NAMESPACE_BEGIN

class RotateToAction;
FE_create_shared_Ptr(RotateToAction);

/**
 * Rotates the target Nodes to x radians in y duration
 */
class RotateToAction : public Action {
    float m_radians;
public:
    RotateToAction(double duration, float radians);
    static RotateToActionPtr create(double duration, float radians);
    
    void update();
    void start();
};

FE_NAMESPACE_END
#endif /* RotateToAction_hpp */
