//
//  texture.cpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//  
//

#include "texture.hpp"
#include "engine_helper.hpp"
#include <memory>
// Bits per pixel in created textures
#define TEXTURE_BIT 32

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000
#define gmask 0x00ff0000
#define bmask 0x0000ff00
#define amask 0x000000ff
#else
#define rmask 0x000000ff
#define gmask 0x0000ff00
#define bmask 0x00ff0000
#define amask 0xff000000
#endif

RKT_NAMESPACE_BEGIN

texture_ptr texture::create() {
    auto t = engine_helper::getInstance()->getTextureForKey("empty");
    if (t == nullptr) {
        t = texture_ptr(new texture());
        engine_helper::getInstance()->cacheTexture(t, "empty");
    }
    return t;
}
texture_ptr texture::create(std::string filename) {
    auto t = engine_helper::getInstance()->getTextureForKey(filename);
    if (t == nullptr) {
        t = texture_ptr(new texture());
        t ->init(filename);
        engine_helper::getInstance()->cacheTexture(t, filename);
    }
    return t;
}
texture_ptr texture::create(vec2f size, color4u col) {
    std::stringstream s; s.str("");
    s << size.x << size.y << col.r << col.g << col.b << col.a;
    auto t = engine_helper::getInstance()->getTextureForKey(s.str());
    if (t == nullptr) {
        t = texture_ptr(new texture());
        t->init(size,col);
        engine_helper::getInstance()->cacheTexture(t, s.str());
    }
    return t;
}
texture_ptr texture::create(texture_ptr source, rectangle rectangle) {
    std::stringstream s; s.str("");
    s << source << rectangle.origin.x << rectangle.origin.y << rectangle.size.x << rectangle.size.y;
    auto t = engine_helper::getInstance()->getTextureForKey(s.str());
    if (t == nullptr) {
        t = texture_ptr(new texture());
        t->init(source,rectangle);
        engine_helper::getInstance()->cacheTexture(t, s.str());
    }
    return t;
}

texture_ptr texture::create(SDL_Surface *surface) {
    auto t = texture_ptr(new texture());
    t->mTexture = SDL_CreateTextureFromSurface(engine_helper::getInstance()->getRenderer(), surface);
    int w,h; SDL_QueryTexture(t->mTexture, NULL, NULL, &w, &h);
    t->mSize = vec2f_make(w, h);
    return t;
}



bool texture::init() {
    SDL_Surface *mys = SDL_CreateRGBSurface(0,0,0,TEXTURE_BIT,rmask, gmask, bmask, amask);
    mTexture = SDL_CreateTextureFromSurface(engine_helper::getInstance()->getRenderer(), mys);
    SDL_FreeSurface(mys);
    return true;
}
bool texture::init(std::string filename) { // load image from path
    SDL_Surface *mys = IMG_Load(filename.c_str());
    mTexture = SDL_CreateTextureFromSurface(engine_helper::getInstance()->getRenderer(), mys);
    int w,h; SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);
    mSize = vec2f_make(w, h);
    SDL_FreeSurface(mys);
    return true;
}
bool texture::init(vec2f size, color4u col) {
    SDL_Surface *mys = SDL_CreateRGBSurface(0, size.x, size.y, TEXTURE_BIT, rmask, gmask, bmask, amask);
    SDL_FillRect(mys, NULL, SDL_MapRGBA(mys->format, col.r, col.g, col.b, col.a));
    mTexture = SDL_CreateTextureFromSurface(engine_helper::getInstance()->getRenderer(), mys);
    mSize = size;
    SDL_FreeSurface(mys);
    return true;
}
bool texture::init(texture_ptr source, rectangle rectangle) {
    mTexture = source->mTexture;
    mSize = rectangle.size;
    mRenderOffset = rectangle.origin;
    mSourceTexture = source;
    return true;
}

bool texture::init(texture_ptr tex) {
    mTexture = tex->mTexture;
    return true;
}
bool texture::init(SDL_Surface *surface) {
    mTexture = SDL_CreateTextureFromSurface(engine_helper::getInstance()->getRenderer(), surface);
    int w,h; SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);
    mSize = vec2f_make(w, h);
    return true;
}


texture::~texture() {
    if (mSourceTexture == nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
    } else mSourceTexture.reset();
}




vec2f texture::getSize() {
    return mSize;
}
vec2f texture::getRenderOffset() {
    return mRenderOffset;
}

SDL_Texture* texture::sdlTexture() {
    return mTexture;
}


RKT_NAMESPACE_END
