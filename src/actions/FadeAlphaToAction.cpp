//
//  FadeAlphaToAction.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "FadeAlphaToAction.hpp"

namespace FE {

inline int NormalizeAlpha(int i) {
    if (i > 255)
        return 255;
    else if (i < 0)
        return 0;
    return i;
}


FadeAlphaToActionPtr FadeAlphaToAction::create(double pduration, int dAlpha) {
    FadeAlphaToActionPtr p(new FadeAlphaToAction());
    p->init(pduration, dAlpha);
    return p;
}


bool FadeAlphaToAction::init(double pduration, int dAlpha) {
    changeInValue = dAlpha;
    duration = pduration*1000;
    m_alpha = dAlpha;
    return true;
}

void FadeAlphaToAction::update() {
    target->setAlpha(currentDoubleValue());
    if (SDL_GetTicks()-startTick > duration) finished = true, target->setAlpha(changeInValue+startValue);
}

void FadeAlphaToAction::start()  {
    startTick = SDL_GetTicks();
    startValue = ((Sprite*)target)->getAlpha();
    changeInValue = m_alpha - startValue;
}


} // namespace FE
