//
//  FadeAlphaToAction.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "FadeAlphaToAction.hpp"

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
    alphaValue = dAlpha;
    duration = pduration*1000;
    return true;
}

void FadeAlphaToAction::update() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    
    int a = startAlpha-((startAlpha - alphaValue)*(passedTime/duration));
    
    target->setAlpha(NormalizeAlpha(a));
    
    if (passedTime >= duration) finished = true, target->setAlpha(alphaValue);
}

void FadeAlphaToAction::start()  {
    startTick = SDL_GetTicks();
    startAlpha = ((Sprite*)target)->getAlpha();
}


