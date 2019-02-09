//
//  CallbackAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 24.12.15.
//  
//

#include "CallbackAction.hpp"

RKT_NAMESPACE_BEGIN

CallbackAction_ptr CallbackAction::create(CallbackActionCallback callback) {
    CallbackAction_ptr p(new CallbackAction());
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
    finished = false;
}

    
RKT_NAMESPACE_END
