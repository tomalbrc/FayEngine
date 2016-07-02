//
//  SpriteAnimationAction.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 20.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "SpriteAnimationAction.hpp"

FE_NAMESPACE_BEGIN

SpriteAnimationAction::~SpriteAnimationAction() {
    textures.clear();
}

SpriteAnimationActionPtr SpriteAnimationAction::create(double secondsPerFrame, std::vector< TexturePtr > textures) {
    return create(secondsPerFrame, textures, true);
}

SpriteAnimationActionPtr SpriteAnimationAction::create(double secondsPerFrame, std::vector< TexturePtr > textures, bool shouldRestoreOriginal) {
    SpriteAnimationActionPtr p(new SpriteAnimationAction());
    p->init(secondsPerFrame, textures, shouldRestoreOriginal);
    return p;
}


bool SpriteAnimationAction::init(double secondsPerFrame, std::vector< TexturePtr > s, bool shouldRestoreOriginal) {
    mShouldRestoreOriginal = shouldRestoreOriginal;
    duration = secondsPerFrame*1000;
    textures = s;
    return true;
}


void SpriteAnimationAction::update() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    if ((passedTime)/duration > 1.0) {
        finished = true;
        if (mShouldRestoreOriginal && mOriginalTexture != nullptr)
            ((Sprite*)target)->setTexture(mOriginalTexture);
        return;
    }
    
    double mark = 1.f/textures.size();
    int index = floor((passedTime/duration)/mark);
    if (index < textures.size()) ((Sprite*)this->target)->setTexture(textures[index]), FELog("Ran texture");
    if (textures.size() > 1) FELog("Size of Textures size of: "<<textures.size()<<", idx: "<<index);
}

void SpriteAnimationAction::start()  {
    mOriginalTexture = ((Sprite *)target)->getTexture();
    startTick = SDL_GetTicks();
    finished = false;
}

    
FE_NAMESPACE_END
