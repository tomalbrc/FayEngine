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
    radValue = radians;
    duration = pduration*1000;
}

void RotateByAction::update() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    
    auto singleStep = radValue / duration; // TODO: MAKE CODE
    
    //auto a = mStartRot-((mStartRot - mDestRot)*(passedTime/duration));
    
    target->setZRotation(singleStep);
    
    if (passedTime >= duration) finished = true;//, target->setZRotation(mDestRot);
}

void RotateByAction::start()  {
    startTick = SDL_GetTicks();
}