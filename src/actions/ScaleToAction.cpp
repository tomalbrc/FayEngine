//
//  ScaleToAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 25.12.15.
//  
//

#include "ScaleToAction.hpp"

RKT_NAMESPACE_BEGIN

ScaleToAction_ptr ScaleToAction::create(double pduration, double destScale) {
    return ScaleToAction_ptr(new ScaleToAction(pduration,destScale));
}

ScaleToAction::ScaleToAction(double pduration, double destScale) : Action() {
    m_scale = Vec2Make(destScale, destScale);
    duration = pduration*1000;
}

void ScaleToAction::update() {
    target->setScale(currentVec2Value());
    if (SDL_GetTicks()-startTick > duration) finished = true, target->setScale(changeInVec2Value+startVec2Value);
}

void ScaleToAction::start()  {
    startTick = SDL_GetTicks();
    startVec2Value = target->getScale();
    changeInVec2Value = m_scale - startVec2Value;
    finished = false;
}


RKT_NAMESPACE_END
