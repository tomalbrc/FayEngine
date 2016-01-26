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
    moveValue = offset;
    duration = pduration*1000;
    return true;
}

void MoveByAction::update() {
    if (finished) return;
    
    Uint32 passedTime = SDL_GetTicks() - startTick;
    
    auto pos = targetStartPos + (moveValue*(passedTime/duration));
    target->setPosition(pos);
    
    if (passedTime >= duration) finished = true, target->setPosition(targetStartPos+moveValue);
}

void MoveByAction::start()  {
    startTick = SDL_GetTicks();
    targetStartPos = target->getPosition();
}
