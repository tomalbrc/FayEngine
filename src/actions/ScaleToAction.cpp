//
//  ScaleToAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 25.12.15.
//  
//

#include "ScaleToAction.hpp"

FE_NAMESPACE_BEGIN

ScaleToActionPtr ScaleToAction::create(double pduration, double destScale) {
    return ScaleToActionPtr(new ScaleToAction(pduration,destScale));
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


FE_NAMESPACE_END
