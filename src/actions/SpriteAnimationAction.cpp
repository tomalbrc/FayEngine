//
//  SpriteAnimationAction.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 20.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "SpriteAnimationAction.hpp"

SpriteAnimationAction::~SpriteAnimationAction() {
    textures.clear();
}

SpriteAnimationActionPtr SpriteAnimationAction::create(double secondsPerFrame, std::vector< TexturePtr > s) {
    SpriteAnimationActionPtr p(new SpriteAnimationAction());
    p->init(secondsPerFrame, s);
    return p;
}

bool SpriteAnimationAction::init(double secondsPerFrame, std::vector< TexturePtr > s) {
    duration = secondsPerFrame*1000;
    textures = s;
    return true;
}


void SpriteAnimationAction::update() {
    if (target == nullptr || finished) return;
    
    Uint32 passedTime = SDL_GetTicks() - startTick;
    if ((passedTime)/duration >= 1.0) {
        finished = true; return;
    }
    
    double mark = 1.f/textures.size();
    int index = floor((passedTime/duration)/mark);
    ((Sprite*)this->target)->setTexture(textures[index]);
}

void SpriteAnimationAction::start()  {
    startTick = SDL_GetTicks();
}

