//
//  RotateToAction.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 25.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "RotateToAction.hpp"

RotateToActionPtr RotateToAction::create(double pduration, double radians) {
    return RotateToActionPtr(new RotateToAction(pduration,radians));
}

RotateToAction::RotateToAction(double pduration, double radians) : Action() {
    changeInValue = radians; // TODO: Something is not right here!!!! Rotate to != Rotate by!!!
    duration = pduration*1000;
}

void RotateToAction::update() {
    target->setZRotation(currentDoubleValue());
    if (SDL_GetTicks() - startTick >= duration) finished = true, target->setZRotation(changeInValue);
}

void RotateToAction::start()  {
    startTick = SDL_GetTicks();
    startValue = target->getZRotation();
}


