//
//  rotate_to_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 25.12.15.
//  
//

#include "rotate_to_action.hpp"

RKT_NAMESPACE_BEGIN

rotate_to_action_ptr rotate_to_action::create(double pduration, float radians) {
    return rotate_to_action_ptr(new rotate_to_action(pduration,radians));
}

rotate_to_action::rotate_to_action(double pduration, float radians) : action() {
    changeInValue = radians; // TODO: Something is not right here!!!! Rotate to != Rotate by!!!
    duration = pduration*1000;
}

void rotate_to_action::update() {
    if (finished) return;
    target->setZRotation(currentDoubleValue());
    if (SDL_GetTicks() - startTick > duration) finished = true, target->setZRotation(changeInValue+startValue);
}

void rotate_to_action::start()  {
    startTick = SDL_GetTicks();
    startValue = target->getZRotation();
    changeInValue -= startValue;
    finished = false;
}

RKT_NAMESPACE_END

