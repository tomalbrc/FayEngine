//
//  MoveByAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#include "MoveByAction.hpp"

RKT_NAMESPACE_BEGIN

MoveByAction_ptr MoveByAction::create(double pduration, Vec2 offset) {
    MoveByAction_ptr p(new MoveByAction());
    p->init(pduration, offset);
    return p;
}

bool MoveByAction::init(double pduration, Vec2 offset) {
    changeInVec2Value = offset;
    duration = pduration*1000;
    return true;
}

void MoveByAction::update() {
    auto popos = currentVec2Value();
    target->setPosition(popos);
    if (SDL_GetTicks()-startTick > duration) finished = true, target->setPosition(changeInVec2Value+startVec2Value);
}

void MoveByAction::start()  {
    startTick = SDL_GetTicks();
    startVec2Value = target->getPosition();
    finished = false;

}

RKT_NAMESPACE_END



