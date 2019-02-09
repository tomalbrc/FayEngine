//
//  rotate_by_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 19.02.16.
//  
//

#include "rotate_by_action.hpp"

RKT_NAMESPACE_BEGIN

rotate_by_action_ptr rotate_by_action::create(double pduration, double radians) {
    return rotate_by_action_ptr(new rotate_by_action(pduration,radians));
}

rotate_by_action::rotate_by_action(double pduration, double radians) : action() {
    changeInValue = radians;
    duration = pduration*1000;
}

void rotate_by_action::update() {
    if (finished) return;
    target->setZRotation(currentDoubleValue());
    if (SDL_GetTicks()-startTick > duration) finished = true, target->setZRotation(changeInValue+startValue);
}

void rotate_by_action::start()  {
    startTick = SDL_GetTicks();
    startValue = target->getZRotation();
    finished = false;
}


RKT_NAMESPACE_END
