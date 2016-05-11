//
//  RotateByAction.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 19.02.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#include "RotateByAction.hpp"

RotateByActionPtr RotateByAction::create(double pduration, double radians) {
    return RotateByActionPtr(new RotateByAction(pduration,radians));
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
}


