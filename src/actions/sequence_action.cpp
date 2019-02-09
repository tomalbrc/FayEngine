//
//  sequence_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#include "sequence_action.hpp"

RKT_NAMESPACE_BEGIN

sequence_action_ptr sequence_action::create(std::vector< action_ptr > actions) {
    sequence_action_ptr p(new sequence_action());
    p->init(std::move(actions));
    return p;
}


bool sequence_action::init(std::vector< action_ptr > actions) {
    if (action::init()) {
        mActions = std::move(actions);
        return true;
    } return false;
}

sequence_action::~sequence_action() {
    mActions.clear();
}

void sequence_action::update() {
    if (target == nullptr || finished) return;
    
    if (mActions[currentIndex]->finished) {
        currentIndex++;
        if (currentIndex == mActions.size()) {
            finished = true;
        }
        else prepareCurrentAction();
    } else mActions[currentIndex]->update();
}

void sequence_action::start()  {
    startTick = SDL_GetTicks();
    currentIndex = 0;
    if (mActions.size() > 0) prepareCurrentAction();
    else finished = true;
    
    for (auto&& a : mActions) {
        a->finished = false;
    }
}

void sequence_action::prepareCurrentAction() {
    mActions[currentIndex]->target = target;
    mActions[currentIndex]->start();
}


RKT_NAMESPACE_END
