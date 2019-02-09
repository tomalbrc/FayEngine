//
//  jump_by_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 18.05.16.
//  
//

#include "jump_by_action.hpp"

RKT_NAMESPACE_BEGIN

jump_by_action_ptr jump_by_action::create(double pduration, vec2f position, float height, int jumps) {
    return jump_by_action_ptr(new jump_by_action(pduration,position, height, jumps));
}


jump_by_action::jump_by_action(double pduration, vec2f position, float height, int jumps) : action() {
    changeInVec2Value = position;
    duration = pduration*1000;
    m_jumps = jumps;
    m_height = height;
}

void jump_by_action::update() {
    if (finished) return;
    
    auto time = (SDL_GetTicks() - startTick)/duration;
    float frac = fmodf((time * m_jumps), 1.f);
    
    float y = m_height * 4.f * frac * (1.f-frac);
    y += changeInVec2Value.y * time;
    
    auto currentPos = target->getPosition();
    
    auto diff = currentPos - m_previousPos;
    startVec2Value = diff + startVec2Value;
    
    float x = changeInVec2Value.x * time;
    
    auto newPos = startVec2Value + vec2f_make(x, y);
    target->setPosition(newPos);
    
    m_previousPos = newPos;
    
    if (SDL_GetTicks()-startTick >= duration) finished = true, target->setPosition(changeInVec2Value+startVec2Value);
}

void jump_by_action::start()  {
    startTick = SDL_GetTicks();
    startVec2Value = target->getPosition();
    m_previousPos = startVec2Value;
    finished = false;
}


RKT_NAMESPACE_END
