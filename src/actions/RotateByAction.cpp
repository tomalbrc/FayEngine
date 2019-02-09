//
//  RotateByAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 19.02.16.
//  
//

#include "RotateByAction.hpp"

RKT_NAMESPACE_BEGIN

RotateByAction_ptr RotateByAction::create(double pduration, double radians) {
    return RotateByAction_ptr(new RotateByAction(pduration,radians));
}

RotateByAction::RotateByAction(double pduration, double radians) : Action() {
    changeInValue = radians;
    duration = pduration*1000;
}

void RotateByAction::update() {
    if (finished) return;
    target->setZRotation(currentDoubleValue());
    if (SDL_GetTicks()-startTick > duration) finished = true, target->setZRotation(changeInValue+startValue);
}

void RotateByAction::start()  {
    startTick = SDL_GetTicks();
    startValue = target->getZRotation();
    finished = false;
}


RKT_NAMESPACE_END
