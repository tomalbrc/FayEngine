//
//  RepeatAction.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 29.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "RepeatAction.hpp"

RepeatActionPtr RepeatAction::create(ActionPtr action, int times) {
    return RepeatActionPtr(new RepeatAction(action,times));
}

RepeatAction::RepeatAction(ActionPtr action, int times) : Action() {
    mTargetAction = action;
    mRepeatTimes = times;
    mForever = mRepeatTimes == 0;
}

RepeatAction::~RepeatAction() {
    mTargetAction = NULL;
}

void RepeatAction::update() {
    if (finished) return;
    
    if (mTargetAction->finished) {
        mRepeatTimes--;
        if (mRepeatTimes <= 0 && mForever) {
            mTargetAction->finished = false;
            target->runAction(mTargetAction);
        } else if (mRepeatTimes <= 0) {
            finished = true;
            return;
        }
    }
    
    mTargetAction->update();
}

void RepeatAction::start()  {
    target->runAction(mTargetAction);
    startTick = SDL_GetTicks();
}

