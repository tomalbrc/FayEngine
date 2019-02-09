//
//  jump_by_action.hpp
//  rawket
//
//  Created by Tom Albrecht on 18.05.16.
//  
//

#ifndef JumpByAction_hpp
#define JumpByAction_hpp

#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class jump_by_action;
RKT_create_ptr(jump_by_action);

class jump_by_action: public action {
    float m_height;
    int m_jumps;
    vec2f m_previousPos;
public:
    jump_by_action(double pduration, vec2f position, float height, int jumps);
    static jump_by_action_ptr create(double pduration, vec2f position, float height, int jumps);
    
    void update();
    void start();
};

RKT_NAMESPACE_END
#endif /* JumpByAction_hpp */
