//
//  RepeatAction.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 29.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "RepeatAction.hpp"

FE_NAMESPACE_BEGIN

RepeatActionPtr RepeatAction::create(ActionPtr action, int times) {
    return RepeatActionPtr(new RepeatAction(action,times));
}

RepeatAction::RepeatAction(ActionPtr action, int times) : Action() {
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
        if (mForever) {
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
}


} // namespace FE
