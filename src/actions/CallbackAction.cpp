//
//  CallbackAction.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 24.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "CallbackAction.hpp"

FE_NAMESPACE_BEGIN

CallbackActionPtr CallbackAction::create(CallbackActionCallback callback) {
    CallbackActionPtr p(new CallbackAction());
    p->init(callback);
    return p;
}

bool CallbackAction::init(CallbackActionCallback callback) {
    mCallback = callback;
    return true;
}

void CallbackAction::update() {
    if (SDL_GetTicks() - startTick > duration) {
        mCallback();
        finished = true;
    }
}

void CallbackAction::start()  {
    startTick = SDL_GetTicks();
    duration = 0;
}

    
} // namespace FE
