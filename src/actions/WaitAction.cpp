//
//  WaitAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#include "WaitAction.hpp"

RKT_NAMESPACE_BEGIN

WaitAction_ptr WaitAction::create(double dur) {
    return WaitAction_ptr(new WaitAction(dur));
}

WaitAction::WaitAction(double dur) : Action() {
    duration = dur*1000.0;
}

void WaitAction::update() {
    if (SDL_GetTicks()-startTick > duration)
        finished = true;
}

void WaitAction::start()  {
    startTick = SDL_GetTicks();
    finished = false;
}

    
RKT_NAMESPACE_END
