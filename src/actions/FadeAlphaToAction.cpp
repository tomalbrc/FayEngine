//
//  FadeAlphaToAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#include "FadeAlphaToAction.hpp"

RKT_NAMESPACE_BEGIN

inline int NormalizeAlpha(int i) {
    if (i > 255)
        return 255;
    else if (i < 0)
        return 0;
    return i;
}


FadeAlphaToAction_ptr FadeAlphaToAction::create(double pduration, int dAlpha) {
    FadeAlphaToAction_ptr p(new FadeAlphaToAction());
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
    finished = false;

}


RKT_NAMESPACE_END
