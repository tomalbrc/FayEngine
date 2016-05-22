//
//  WaitAction.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 22.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "WaitAction.hpp"

namespace FE {

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
}

    
} // namespace FE
