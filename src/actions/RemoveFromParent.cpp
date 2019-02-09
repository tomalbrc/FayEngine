//
//  RemoveFromParent.cpp
//  rawket
//
//  Created by Tom Albrecht on 10.12.15.
//  
//

#include "RemoveFromParent.hpp"

RKT_NAMESPACE_BEGIN

RemoveFromParentAction_ptr RemoveFromParentAction::create() {
    RemoveFromParentAction_ptr p(new RemoveFromParentAction());
    p->init();
    return p;
}

bool RemoveFromParentAction::init() {
    duration = 0;
    return true;
}


void RemoveFromParentAction::update() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    if (passedTime/duration > 1) finished = true, target->removeFromParent(); // Testing
}

void RemoveFromParentAction::start()  {
    startTick = SDL_GetTicks();
    finished = false;
}

    
RKT_NAMESPACE_END

