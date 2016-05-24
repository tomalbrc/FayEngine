//
//  JumpByAction.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 18.05.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#include "JumpByAction.hpp"

FE_NAMESPACE_BEGIN

JumpByActionPtr JumpByAction::create(double pduration, Vec2 position, float height, int jumps) {
    return JumpByActionPtr(new JumpByAction(pduration,position, height, jumps));
}


JumpByAction::JumpByAction(double pduration, Vec2 position, float height, int jumps) : Action() {
    changeInVec2Value = position;
    duration = pduration*1000;
    m_jumps = jumps;
    m_height = height;
}

void JumpByAction::update() {
    if (finished) return;
    
    auto time = (SDL_GetTicks() - startTick)/duration;
    float frac = fmodf((time * m_jumps), 1.f);
    
    float y = m_height * 4.f * frac * (1.f-frac);
    y += changeInVec2Value.y * time;
    
    auto currentPos = target->getPosition();
    
    auto diff = currentPos - m_previousPos;
    startVec2Value = diff + startVec2Value;
    
    float x = changeInVec2Value.x * time;
    
    auto newPos = startVec2Value + Vec2Make(x, y);
    target->setPosition(newPos);
    
    m_previousPos = newPos;
    
    if (SDL_GetTicks()-startTick >= duration) finished = true, target->setPosition(changeInVec2Value+startVec2Value);
}

void JumpByAction::start()  {
    startTick = SDL_GetTicks();
    startVec2Value = target->getPosition();
    m_previousPos = startVec2Value;
}


} // namespace FE
