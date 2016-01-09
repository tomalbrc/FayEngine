//
//  RotateAction.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 25.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "RotateAction.hpp"

RotateToActionPtr RotateToAction::create(double pduration, int destRot) {
    return RotateToActionPtr(new RotateToAction(pduration,destRot));
}

RotateToAction::RotateToAction(double pduration, int destRot) : Action() {
    mDestRot = destRot;
    duration = pduration*1000;
}

void RotateToAction::update() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    
    auto a = mStartRot-((mStartRot - mDestRot)*(passedTime/duration));
    
    target->setZRotation(a);
    
    if (passedTime >= duration) finished = true, target->setZRotation(mDestRot);
}

void RotateToAction::start()  {
    startTick = SDL_GetTicks();
    mStartRot = target->getZRotation();
}
