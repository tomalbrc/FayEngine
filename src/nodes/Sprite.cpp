//
//  Sprite.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 08.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Sprite.hpp"


SpritePtr Sprite::create() {
    SpritePtr ss(new Sprite());
    ss->init();
    return ss;
}
SpritePtr Sprite::create(TexturePtr s) {
    SpritePtr ss(new Sprite());
    ss->init(s);
    return ss;
}
SpritePtr Sprite::create(Vec2 dimensions) {
    SpritePtr ss(new Sprite());
    ss->init(dimensions);
    return ss;
}
SpritePtr Sprite::create(std::string filename) {
    SpritePtr ss(new Sprite());
    ss->init(filename);
    return ss;
}

bool Sprite::init() {
    return Node::init();
}

bool Sprite:: init(TexturePtr s) {
    if (Node::init()) {
        setTexture(s);
        return true;
    }
    return false;
}
bool Sprite:: init(Vec2 dimensions) {
    if (Node::init()) {
        setTexture(Texture::create(Vec2Make(dimensions.x, dimensions.y), ColorWhiteColor()));
        return true;
    }
    return init();
}
bool Sprite::init(std::string filename) {
    if (Node::init()) {
        setTexture(Texture::create(filename));
        return true;
    }
    return false;
}

Sprite:: ~Sprite() {
    mTexture.reset();
}





Vec2 Sprite::getSize() {
    return mSize*getScale();
}


void Sprite::setTexture(TexturePtr tex) {
    mTexture.reset();
    mTexture = tex;
    if (tex != nullptr) mSize = tex->getSize();
}
TexturePtr Sprite::getTexture() {
    return mTexture;
}

void Sprite::setAnchorPoint(Vec2 ap) {
    mAnchorPoint = ap;
}
Vec2 Sprite::getAnchorPoint() {
    return mAnchorPoint;
}


// Rect in parent coordinate system
Rect Sprite::getRect() {
    return RectMake(getPosition(), getSize());;
}

// Rect in own coordinate system
Rect Sprite::getBoundingBox() {
    return RectMake(Vec2Null(), getSize());
}



void Sprite::render(SDL_Renderer *renderer) { // render into scene / Surfac
    auto po = convertToWorldSpace(Vec2Null());
    if (this->getTexture() != nullptr) { // Draw this sprite if the tex is set
        auto s = getSize();
        
        auto sRect = RectMake(mTexture->getRenderOffset(), mTexture->getSize());
        auto dRect = RectMake(po,s);
        
        SDL_Rect ddRect;
        ddRect.x = dRect.origin.x, ddRect.y = dRect.origin.y, ddRect.w = dRect.size.x, ddRect.h = dRect.size.y;
        ddRect.x -= mAnchorPoint.x * ddRect.w;
        ddRect.y -= mAnchorPoint.y * ddRect.h;
        
        SDL_Rect ssRect;
        ssRect.x = sRect.origin.x, ssRect.y = sRect.origin.y, ssRect.w = sRect.size.x, ssRect.h = sRect.size.y;
        
        SDL_SetTextureAlphaMod(mTexture->sdlTexture(), getAlpha()); // temporarily apply Sprites alpha value
        SDL_RenderCopyEx(renderer, mTexture->sdlTexture(), &ssRect, &ddRect, getZRotation(), NULL, SDL_FLIP_NONE);
    }
    
    Node::render(renderer);
}
