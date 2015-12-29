//
//  RemoveFromParent.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 10.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "RemoveFromParent.hpp"

RemoveFromParentActionPtr RemoveFromParentAction::create() {
    RemoveFromParentActionPtr p(new RemoveFromParentAction());
    p->init(0);
    return p;
}
RemoveFromParentActionPtr RemoveFromParentAction::create(double delay) {
    RemoveFromParentActionPtr p(new RemoveFromParentAction());
    p->init(delay);
    return p;
}


bool RemoveFromParentAction::init() {
    return init(0);
}

bool RemoveFromParentAction::init(double delay) {
    if (Action::init()) {
        duration = delay*1000;
        return true;
    }
    return false;
}

void RemoveFromParentAction::update() {
    if (target == nullptr) return;

    Uint32 passedTime = SDL_GetTicks() - startTick;
    if (passedTime/duration >= 1) finished = true, target->removeFromParent();
}

void RemoveFromParentAction::start()  {
    startTick = SDL_GetTicks();
}

