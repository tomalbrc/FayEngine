//
//  SequenceAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#include "SequenceAction.hpp"

RKT_NAMESPACE_BEGIN

SequenceAction_ptr SequenceAction::create(std::vector< Action_ptr > actions) {
    SequenceAction_ptr p(new SequenceAction());
    p->init(std::move(actions));
    return p;
}


bool SequenceAction::init(std::vector< Action_ptr > actions) {
    if (Action::init()) {
        mActions = std::move(actions);
        return true;
    } return false;
}

SequenceAction::~SequenceAction() {
    mActions.clear();
}

void SequenceAction::update() {
    if (target == nullptr || finished) return;
    
    if (mActions[currentIndex]->finished) {
        currentIndex++;
        if (currentIndex == mActions.size()) {
            finished = true;
        }
        else prepareCurrentAction();
    } else mActions[currentIndex]->update();
}

void SequenceAction::start()  {
    startTick = SDL_GetTicks();
    currentIndex = 0;
    if (mActions.size() > 0) prepareCurrentAction();
    else finished = true;
    
    for (auto&& a : mActions) {
        a->finished = false;
    }
}

void SequenceAction::prepareCurrentAction() {
    mActions[currentIndex]->target = target;
    mActions[currentIndex]->start();
}


RKT_NAMESPACE_END
