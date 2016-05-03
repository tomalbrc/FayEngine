//
//  MoveByAction.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "MoveByAction.hpp"

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
    if (SDL_GetTicks()-startTick >= duration) finished = true, target->setPosition(changeInVec2Value+startVec2Value);
}

void MoveByAction::start()  {
    startTick = SDL_GetTicks();
    startVec2Value = target->getPosition();
}



