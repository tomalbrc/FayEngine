//
//  scale_to_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 25.12.15.
//  
//

#include "scale_to_action.hpp"

RKT_NAMESPACE_BEGIN

scale_to_action_ptr scale_to_action::create(double pduration, double destScale) {
    return scale_to_action_ptr(new scale_to_action(pduration,destScale));
}

scale_to_action::scale_to_action(double pduration, double destScale) : action() {
    m_scale = vec2f_make(destScale, destScale);
    duration = pduration*1000;
}

void scale_to_action::update() {
    target->setScale(currentVec2Value());
    if (SDL_GetTicks()-startTick > duration) finished = true, target->setScale(changeInVec2Value+startVec2Value);
}

void scale_to_action::start()  {
    startTick = SDL_GetTicks();
    startVec2Value = target->getScale();
    changeInVec2Value = m_scale - startVec2Value;
    finished = false;
}


RKT_NAMESPACE_END
