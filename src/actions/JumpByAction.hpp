//
//  JumpByAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 18.05.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef JumpByAction_hpp
#define JumpByAction_hpp

#include "Action.hpp"
#include "Sprite.hpp"

FE_NAMESPACE_BEGIN

class JumpByAction;
FE_create_Ptr(JumpByAction);

class JumpByAction: public Action {
    float m_height;
    int m_jumps;
    Vec2 m_previousPos;
public:
    JumpByAction(double pduration, Vec2 position, float height, int jumps);
    static JumpByActionPtr create(double pduration, Vec2 position, float height, int jumps);
    
    void update();
    void start();
};

} // namespace FE
#endif /* JumpByAction_hpp */
