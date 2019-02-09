//
//  repeat_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 29.12.15.
//  
//

#include "repeat_action.hpp"

RKT_NAMESPACE_BEGIN

repeat_action_ptr repeat_action::create(action_ptr action, int times) {
    return repeat_action_ptr(new repeat_action(action,times));
}

repeat_action::repeat_action(action_ptr paction, int times) : action{} {
    mTargetAction = paction;
    mRepeatTimes = times;
    mForever = mRepeatTimes == 0;
}

repeat_action::~repeat_action() {
    mTargetAction.reset();
}

void repeat_action::update() {
    if (target == nullptr) return;
    
    if (mTargetAction->finished) {
        mRepeatTimes--;
        if (mForever || mRepeatTimes > 0) {
            mTargetAction->finished = false;
            mTargetAction->start();
        } else if (mRepeatTimes <= 0) {
            mTargetAction.reset();
            finished = true;
            return;
        }
    }
    
    mTargetAction->update();
}

void repeat_action::start()  {
    mTargetAction->target = target;
    mTargetAction->start();
    startTick = SDL_GetTicks();
    finished = false;
}


RKT_NAMESPACE_END
