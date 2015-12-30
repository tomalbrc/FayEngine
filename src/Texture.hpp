//
//  Texture.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Node.hpp"

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

class Texture {
public:
    static TexturePtr create();
    static TexturePtr create(std::string filename);
    static TexturePtr create(Vec2 size, Color col);
    static TexturePtr create(TexturePtr tex, Rect rect);
    static TexturePtr create(TexturePtr tex); // Passes ownership to EngineHelper
    static TexturePtr create(SDL_Surface *surface);
    ~Texture();
    
    void setSize(Vec2 size);
    Vec2 getSize();
    Vec2 getRenderOffset();
    
    SDL_Texture* sdlTexture();
    
private:
    TexturePtr mSourceTexture = NULL;
    SDL_Texture *mTexture = NULL;
    std::shared_ptr<Texture> mBatchTexture;
    Vec2 mRenderOffset = Vec2Null();
    Vec2 mSize = Vec2Null();
    
    bool init();
    bool init(std::string filename); // load image from path
    bool init(Vec2 size, Color col);
    bool init(TexturePtr source, Rect rect);
    bool init(TexturePtr tex); // Passes ownership to EngineHelper
    bool init(SDL_Surface *surface);
};
#endif /* Texture_hpp */
