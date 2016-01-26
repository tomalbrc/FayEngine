//
//  ScaleToAction.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 25.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "ScaleToAction.hpp"

ScaleToActionPtr ScaleToAction::create(double pduration, double destScale) {
    return ScaleToActionPtr(new ScaleToAction(pduration,destScale));
}

ScaleToAction::ScaleToAction(double pduration, double destScale) : Action() {
    mDestScale = Vec2Make(destScale, destScale);
    duration = pduration*1000;
}

void ScaleToAction::update() {
    if (target == nullptr) return;

    Uint32 passedTime = SDL_GetTicks() - startTick;
    auto a = mStartScale-((mStartScale - mDestScale)*(passedTime/duration));
    target->setScale(a);
    
    if (passedTime >= duration) finished = true, target->setScale(mDestScale);
}

void ScaleToAction::start()  {
    startTick = SDL_GetTicks();
    mStartScale = target->getScale();
}
