//
//  SpriteAnimationAction.cpp
//  rawket
//
//  Created by Tom Albrecht on 20.12.15.
//  
//

#include "SpriteAnimationAction.hpp"

RKT_NAMESPACE_BEGIN

SpriteAnimationAction::~SpriteAnimationAction() {
    textures.clear();
}

SpriteAnimationAction_ptr SpriteAnimationAction::create(double secondsPerFrame, std::vector< Texture_ptr > textures) {
    return create(secondsPerFrame, textures, true);
}

SpriteAnimationAction_ptr SpriteAnimationAction::create(double secondsPerFrame, std::vector< Texture_ptr > textures, bool shouldRestoreOriginal) {
    SpriteAnimationAction_ptr p(new SpriteAnimationAction());
    p->init(secondsPerFrame, textures, shouldRestoreOriginal);
    return p;
}


bool SpriteAnimationAction::init(double secondsPerFrame, std::vector< Texture_ptr > s, bool shouldRestoreOriginal) {
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
    if (index < textures.size()) ((Sprite*)this->target)->setTexture(textures[index]);//, RKTLog("Ran texture");
    //if (textures.size() > 1) RKTLog("Size of Textures size of: "<<textures.size()<<", idx: "<<index);
}

void SpriteAnimationAction::start()  {
    mOriginalTexture = ((Sprite *)target)->getTexture();
    startTick = SDL_GetTicks();
    finished = false;
}

    
RKT_NAMESPACE_END
