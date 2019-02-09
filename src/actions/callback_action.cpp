//
//  callback_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 24.12.15.
//  
//

#include "callback_action.hpp"

RKT_NAMESPACE_BEGIN

callback_action_ptr callback_action::create(CallbackActionCallback callback) {
    callback_action_ptr p(new callback_action());
    p->init(callback);
    return p;
}

bool callback_action::init(CallbackActionCallback callback) {
    mCallback = callback;
    return true;
}

void callback_action::update() {
    if (SDL_GetTicks() - startTick > duration) {
        mCallback();
        finished = true;
    }
}

void callback_action::start()  {
    startTick = SDL_GetTicks();
    duration = 0;
    finished = false;
}

    
RKT_NAMESPACE_END
