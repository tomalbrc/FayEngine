//
//  RotateToAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 25.12.15.
//  
//

#include "RotateToAction.hpp"

RKT_NAMESPACE_BEGIN

RotateToAction_ptr RotateToAction::create(double pduration, float radians) {
    return RotateToAction_ptr(new RotateToAction(pduration,radians));
}

RotateToAction::RotateToAction(double pduration, float radians) : Action() {
    changeInValue = radians; // TODO: Something is not right here!!!! Rotate to != Rotate by!!!
    duration = pduration*1000;
}

void RotateToAction::update() {
    if (finished) return;
    target->setZRotation(currentDoubleValue());
    if (SDL_GetTicks() - startTick > duration) finished = true, target->setZRotation(changeInValue+startValue);
}

void RotateToAction::start()  {
    startTick = SDL_GetTicks();
    startValue = target->getZRotation();
    changeInValue -= startValue;
    finished = false;
}

RKT_NAMESPACE_END

