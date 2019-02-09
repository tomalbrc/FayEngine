//
//  fade_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#include "fade_action.hpp"

RKT_NAMESPACE_BEGIN

inline int NormalizeAlpha(int i) {
    if (i > 255)
        return 255;
    else if (i < 0)
        return 0;
    return i;
}


fade_action_ptr fade_action::create(double pduration, int dAlpha) {
    fade_action_ptr p(new fade_action());
    p->init(pduration, dAlpha);
    return p;
}


bool fade_action::init(double pduration, int dAlpha) {
    changeInValue = dAlpha;
    duration = pduration*1000;
    m_alpha = dAlpha;
    return true;
}

void fade_action::update() {
    target->setAlpha(currentDoubleValue());
    if (SDL_GetTicks()-startTick > duration) finished = true, target->setAlpha(changeInValue+startValue);
}

void fade_action::start()  {
    startTick = SDL_GetTicks();
    startValue = ((sprite*)target)->getAlpha();
    changeInValue = m_alpha - startValue;
    finished = false;

}


RKT_NAMESPACE_END
