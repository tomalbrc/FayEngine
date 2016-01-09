//
//  SequenceAction.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 22.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "SequenceAction.hpp"

SequenceActionPtr SequenceAction::create(std::vector< ActionPtr > actions) {
    SequenceActionPtr p(new SequenceAction());
    p->init(std::move(actions));
    return p;
}


bool SequenceAction::init(std::vector< ActionPtr > actions) {
    if (Action::init()) {
        mActions = std::move(actions);
        return true;
    } return false;
}

SequenceAction::~SequenceAction() {
    mActions.clear();
}

void SequenceAction::update() {
    if (mActions.size() == 0 || target == nullptr) return;
    
    if (mActions[currentIndex]->finished) {
        mActions.erase(std::remove(mActions.begin(), mActions.end(), mActions[currentIndex]), mActions.end());
        if (mActions.size()== 0) {
            finished = true;
            return;
        }
        else prepareCurrentAction();
    }
    
    mActions[currentIndex]->update();
}

void SequenceAction::start()  {
    startTick = SDL_GetTicks();
    if (mActions.size() > 0) prepareCurrentAction();
    else finished = true;
}

void SequenceAction::prepareCurrentAction() {
    mActions[currentIndex]->target = target;
    mActions[currentIndex]->start();
}

