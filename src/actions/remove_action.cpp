//
//  RemoveFromParent.cpp
//  rawket
//
//  Created by Tom Albrecht on 10.12.15.
//  
//

#include "remove_action.hpp"

RKT_NAMESPACE_BEGIN

remove_action_ptr remove_action::create() {
    remove_action_ptr p(new remove_action());
    p->init();
    return p;
}

bool remove_action::init() {
    duration = 0;
    return true;
}


void remove_action::update() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    if (passedTime/duration > 1) finished = true, target->removeFromParent(); // Testing
}

void remove_action::start()  {
    startTick = SDL_GetTicks();
    finished = false;
}

    
RKT_NAMESPACE_END

