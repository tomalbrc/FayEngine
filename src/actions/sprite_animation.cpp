//
//  sprite_animation_action.cpp
//  rawket
//
//  Created by Tom Albrecht on 20.12.15.
//  
//

#include "sprite_animation.hpp"

RKT_NAMESPACE_BEGIN

sprite_animation_action::~sprite_animation_action() {
    textures.clear();
}

sprite_animation_action_ptr sprite_animation_action::create(double secondsPerFrame, std::vector< texture_ptr > textures) {
    return create(secondsPerFrame, textures, true);
}

sprite_animation_action_ptr sprite_animation_action::create(double secondsPerFrame, std::vector< texture_ptr > textures, bool shouldRestoreOriginal) {
    sprite_animation_action_ptr p(new sprite_animation_action());
    p->init(secondsPerFrame, textures, shouldRestoreOriginal);
    return p;
}


bool sprite_animation_action::init(double secondsPerFrame, std::vector< texture_ptr > s, bool shouldRestoreOriginal) {
    mShouldRestoreOriginal = shouldRestoreOriginal;
    duration = secondsPerFrame*1000;
    textures = s;
    return true;
}


void sprite_animation_action::update() {
    Uint32 passedTime = SDL_GetTicks() - startTick;
    if ((passedTime)/duration > 1.0) {
        finished = true;
        if (mShouldRestoreOriginal && mOriginalTexture != nullptr)
            ((sprite*)target)->setTexture(mOriginalTexture);
        return;
    }
    
    double mark = 1.f/textures.size();
    int index = floor((passedTime/duration)/mark);
    if (index < textures.size()) ((sprite*)this->target)->setTexture(textures[index]);//, RKTLog("Ran texture");
    //if (textures.size() > 1) RKTLog("Size of Textures size of: "<<textures.size()<<", idx: "<<index);
}

void sprite_animation_action::start()  {
    mOriginalTexture = ((sprite *)target)->getTexture();
    startTick = SDL_GetTicks();
    finished = false;
}

    
RKT_NAMESPACE_END
