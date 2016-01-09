//
//  WaitAction.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 22.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "WaitAction.hpp"

WaitActionPtr WaitAction::create(double dur) {
    return WaitActionPtr(new WaitAction(dur));
}

WaitAction::WaitAction(double dur) : Action() {
    duration = dur*1000.0;
}

void WaitAction::update() {
    if (target == nullptr) return;
    
    if (SDL_GetTicks()-startTick >= duration)
        finished = true;
}

void WaitAction::start()  {
    startTick = SDL_GetTicks();
}

