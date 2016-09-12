//
//  Sprite.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 08.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Sprite.hpp"

FE_NAMESPACE_BEGIN

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
    return mSize;
}


void Sprite::setTexture(TexturePtr tex) {
    mTexture.reset();
    mTexture = tex;
    if (tex != nullptr) mSize = tex->getSize();
}
TexturePtr Sprite::getTexture() {
    return mTexture;
}



BlendMode Sprite::getBlendMode() {
    return m_blendMode;
}

void Sprite::setBlendMode(BlendMode mode) {
    m_blendMode = mode;
}




// Rect in parent coordinate system
Rect Sprite::getRect() {
    return RectMake(getPosition() - (getAnchorPoint()*getSize()), getSize()*getScale());
}

// Rect in own coordinate system
Rect Sprite::getBoundingBox() {
    return RectMake(Vec2Null(), getSize());
}




void Sprite::render(SDL_Renderer *renderer) { // render into scene / Surfac
    if (this->getTexture() != nullptr) { // Draw this sprite if the tex is set
        auto absRot = getZRotation();
        auto absScale = getScale();
        for (auto p = getParent(); p.get() != NULL; p = p->getParent() )
            absScale = absScale * p->getScale(), absRot += p->getZRotation();
        
        auto sRect = RectMake(mTexture->getRenderOffset(), mTexture->getSize());
        auto dRect = RectMake(convertToWorldSpace(Vec2Null()), getSize()*absScale);
        
        dRect = dRect*EngineHelper::getInstance()->getMainWindow()->screenScale();
        
        SDL_Rect ddRect;
        ddRect.x = dRect.origin.x, ddRect.y = dRect.origin.y, ddRect.w = dRect.size.x, ddRect.h = dRect.size.y;
        ddRect.x -= getAnchorPoint().x * ddRect.w;
        ddRect.y -= getAnchorPoint().y * ddRect.h;
        
        SDL_Rect ssRect;
        ssRect.x = sRect.origin.x, ssRect.y = sRect.origin.y, ssRect.w = sRect.size.x, ssRect.h = sRect.size.y;
        
        SDL_Point center;
        center.x = ddRect.w*getAnchorPoint().x;
        center.y = ddRect.h*getAnchorPoint().y;
        
        SDL_SetTextureColorMod(mTexture->sdlTexture(), m_color.r, m_color.g, m_color.b);
        SDL_SetTextureBlendMode(mTexture->sdlTexture(), SDL_BlendMode(m_blendMode));
        SDL_SetTextureAlphaMod(mTexture->sdlTexture(), getAlpha()); // temporarily apply Sprites alpha value
        SDL_RenderCopyEx(renderer, mTexture->sdlTexture(), &ssRect, &ddRect, -RadiansToDegrees(absRot), &center, SDL_FLIP_NONE);
    }
    Node::render(renderer);
}




void Sprite::setColor(Color color) {
    m_color = color;
}
Color Sprite::getColor() {
    return m_color;
}

    
FE_NAMESPACE_END
