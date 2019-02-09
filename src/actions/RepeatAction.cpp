//
//  RepeatAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 29.12.15.
//  
//

#include "RepeatAction.hpp"

RKT_NAMESPACE_BEGIN

RepeatAction_ptr RepeatAction::create(Action_ptr action, int times) {
    return RepeatAction_ptr(new RepeatAction(action,times));
}

RepeatAction::RepeatAction(Action_ptr action, int times) : Action() {
    mTargetAction = action;
    mRepeatTimes = times;
    mForever = mRepeatTimes == 0;
}

RepeatAction::~RepeatAction() {
    mTargetAction.reset();
}

void RepeatAction::update() {
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

void RepeatAction::start()  {
    mTargetAction->target = target;
    mTargetAction->start();
    startTick = SDL_GetTicks();
    finished = false;
}


RKT_NAMESPACE_END
