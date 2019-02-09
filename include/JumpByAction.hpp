//
//  JumpByAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 18.05.16.
//  
//

#ifndef JumpByAction_hpp
#define JumpByAction_hpp

#include "Action.hpp"
#include "Sprite.hpp"

RKT_NAMESPACE_BEGIN

class JumpByAction;
RKT_create__ptr(JumpByAction);

class JumpByAction: public Action {
    float m_height;
    int m_jumps;
    Vec2 m_previousPos;
public:
    JumpByAction(double pduration, Vec2 position, float height, int jumps);
    static JumpByAction_ptr create(double pduration, Vec2 position, float height, int jumps);
    
    void update();
    void start();
};

RKT_NAMESPACE_END
#endif /* JumpByAction_hpp */
