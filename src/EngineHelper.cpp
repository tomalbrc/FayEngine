//
//  EngineHelper.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "EngineHelper.hpp"
#include "SDL_ttf.h"
#include "Texture.hpp"

EngineHelper::EngineHelper() {
    FELog("EngineHelper::EngineHelper()");
}
EngineHelper::~EngineHelper() {
    FELog("EngineHelper::~EngineHelper");
}

EngineHelper* EngineHelper::getInstance() {
    static EngineHelper theInstance;
    return &theInstance;
}



SDL_Renderer* EngineHelper::getRenderer() {
    return gameRenderer;
}
void EngineHelper::setRenderer(SDL_Renderer *r) {
    gameRenderer = r;
}

void EngineHelper::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(2);
    }
    
    if(TTF_Init()==-1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        exit(2);
    }
    
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == -1) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        exit(2);
    }
}




void EngineHelper::setEnableVSync(bool enable) {
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, enable ? "1":"0");
}

Vec2 EngineHelper::getDiplaySize() {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    return Vec2Make(mode.w, mode.h);
}




void EngineHelper::cacheTexture(TexturePtr texture, std::string key) {
    textureCache[key] = texture;
}
void EngineHelper::cacheTextures(std::vector<TexturePtr> textures, std::vector<std::string> keys) {
    for (int i = 0; i < textures.size(); i++) {
        cacheTexture(textures[i], keys[i]);
    }
}
void EngineHelper::removeTextureForKey(std::string key) {
    textureCache.erase(key);
}
void EngineHelper::removeTextureFromCache(TexturePtr tex) {
    for (auto&& iterator = textureCache.begin(); iterator != textureCache.end(); ++iterator) {
        if (iterator->second == tex)  {
            removeTextureForKey(iterator->first);
            break;
        }
    }
}
TexturePtr EngineHelper::getTextureForKey(std::string key) {
    return textureCache[key];
}
void EngineHelper::cleanTextureCache() {
    for(auto&& iterator = textureCache.begin(); iterator != textureCache.end(); iterator++)
        removeTextureForKey(iterator->first);
}

void EngineHelper::removeUnusedTextures() {
    for(auto&& iterator = textureCache.begin(); iterator != textureCache.end();) {
        if (iterator->second.use_count() == 1) FELog("REMOVED UNUSED TEXTURE NAMED "<<iterator->first), iterator = textureCache.erase(iterator);
        else ++iterator;
    }
}

