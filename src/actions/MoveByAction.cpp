//
//  MoveByAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#include "MoveByAction.hpp"

FE_NAMESPACE_BEGIN

MoveByActionPtr MoveByAction::create(double pduration, Vec2 offset) {
    MoveByActionPtr p(new MoveByAction());
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

FE_NAMESPACE_END



