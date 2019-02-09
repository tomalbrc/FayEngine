//
//  wait_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#include "wait_action.hpp"

RKT_NAMESPACE_BEGIN

wait_action_ptr wait_action::create(double dur) {
    return wait_action_ptr(new wait_action(dur));
}

wait_action::wait_action(double dur) : action() {
    duration = dur*1000.0;
}

void wait_action::update() {
    if (SDL_GetTicks()-startTick > duration)
        finished = true;
}

void wait_action::start()  {
    startTick = SDL_GetTicks();
    finished = false;
}

    
RKT_NAMESPACE_END
