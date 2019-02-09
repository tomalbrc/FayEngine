//
//  WaitAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#include "WaitAction.hpp"

FE_NAMESPACE_BEGIN

WaitActionPtr WaitAction::create(double dur) {
    return WaitActionPtr(new WaitAction(dur));
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

    
FE_NAMESPACE_END
