//
//  Texture.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Texture.hpp"
#include "EngineHelper.hpp"
#include <memory>
// Bits per pixel in created textures
#define TEXTURE_BIT 24

TexturePtr Texture::create() {
    auto t = EngineHelper::getInstance()->getTextureForKey("empty");
    if (t == nullptr) {
        t = TexturePtr(new Texture());
        EngineHelper::getInstance()->cacheTexture(t, "empty");
    }
    return t;
}
TexturePtr Texture::create(std::string filename) {
    auto t = EngineHelper::getInstance()->getTextureForKey(filename);
    if (t == nullptr) {
        t = TexturePtr(new Texture());
        t ->init(filename);
        EngineHelper::getInstance()->cacheTexture(t, filename);
    }
    return t;
}
TexturePtr Texture::create(Vec2 size, Color col) {
    std::stringstream s; s.str("");
    s << size.x << size.y << col.r << col.g << col.b << col.a;
    auto t = EngineHelper::getInstance()->getTextureForKey(s.str());
    if (t == nullptr) {
        t = TexturePtr(new Texture());
        t->init(size,col);
        EngineHelper::getInstance()->cacheTexture(t, s.str());
    }
    return t;
}
TexturePtr Texture::create(TexturePtr source, Rect rect) {
    std::stringstream s; s.str("");
    s << source << rect.origin.x << rect.origin.y << rect.size.x << rect.size.y;
    auto t = EngineHelper::getInstance()->getTextureForKey(s.str());
    if (t == nullptr) {
        t = TexturePtr(new Texture());
        t->init(source,rect);
        EngineHelper::getInstance()->cacheTexture(t, s.str());
    }
    return t;
}

TexturePtr Texture::create(SDL_Surface *surface) {
    auto t = TexturePtr(new Texture());
    t->mTexture = SDL_CreateTextureFromSurface(EngineHelper::getInstance()->getRenderer(), surface);
    int w,h; SDL_QueryTexture(t->mTexture, NULL, NULL, &w, &h);
    t->mSize = Vec2Make(w, h);
    return t;
}



bool Texture::init() {
    SDL_Surface *mys = SDL_CreateRGBSurface(0,0,0,TEXTURE_BIT,0,0,0,255);
    mTexture = SDL_CreateTextureFromSurface(EngineHelper::getInstance()->getRenderer(), mys);
    SDL_FreeSurface(mys);
    return true;
}
bool Texture::init(std::string filename) { // load image from path
    SDL_Surface *mys = IMG_Load(filename.c_str());
    mTexture = SDL_CreateTextureFromSurface(EngineHelper::getInstance()->getRenderer(), mys);
    int w,h; SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);
    mSize = Vec2Make(w, h);
    SDL_FreeSurface(mys);
    return true;
}
bool Texture::init(Vec2 size, Color col) {
    SDL_Surface *mys = SDL_CreateRGBSurface(0, size.x, size.y, TEXTURE_BIT, col.r, col.g, col.b, col.a);
    mTexture = SDL_CreateTextureFromSurface(EngineHelper::getInstance()->getRenderer(), mys);
    mSize = size;
    SDL_FreeSurface(mys);
    return true;
}
bool Texture::init(TexturePtr source, Rect rect) {
    mTexture = source->mTexture;
    mSize = rect.size;
    mRenderOffset = rect.origin;
    mSourceTexture = source;
    return true;
}

bool Texture::init(TexturePtr tex) {
    mTexture = tex->mTexture;
    return true;
}
bool Texture::init(SDL_Surface *surface) {
    mTexture = SDL_CreateTextureFromSurface(EngineHelper::getInstance()->getRenderer(), surface);
    int w,h; SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);
    mSize = Vec2Make(w, h);
    return true;
}


Texture::~Texture() {
    if (mSourceTexture == nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
    } else mSourceTexture.reset();
}




Vec2 Texture::getSize() {
    return mSize;
}
Vec2 Texture::getRenderOffset() {
    return mRenderOffset;
}

SDL_Texture* Texture::sdlTexture() {
    return mTexture;
}
