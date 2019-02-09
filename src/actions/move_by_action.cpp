//
//  move_by_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#include "move_by_action.hpp"

RKT_NAMESPACE_BEGIN

move_by_action_ptr move_by_action::create(double pduration, vec2f offset) {
    move_by_action_ptr p(new move_by_action());
    p->init(pduration, offset);
    return p;
}

bool move_by_action::init(double pduration, vec2f offset) {
    changeInVec2Value = offset;
    duration = pduration*1000;
    return true;
}

void move_by_action::update() {
    auto popos = currentVec2Value();
    target->setPosition(popos);
    if (SDL_GetTicks()-startTick > duration) finished = true, target->setPosition(changeInVec2Value+startVec2Value);
}

void move_by_action::start()  {
    startTick = SDL_GetTicks();
    startVec2Value = target->getPosition();
    finished = false;

}

RKT_NAMESPACE_END



