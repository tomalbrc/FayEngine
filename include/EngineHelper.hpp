//
//  EngineHelper.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef EngineHelper_hpp
#define EngineHelper_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "tmxparser.h"

#include "Texture.hpp"

class EngineHelper {
private:
    EngineHelper();
    ~EngineHelper();
    SDL_Renderer *gameRenderer;
    std::map<std::string, TexturePtr> textureCache;
public:
    static EngineHelper *getInstance();
    
    SDL_Renderer* getRenderer();
    void setRenderer(SDL_Renderer *r);
    
    void Init();
    
    void setEnableVSync(bool enable);
    
    Vec2 getDiplaySize();
    
    
    void cacheTexture(TexturePtr texture, std::string key);
    void cacheTextures(std::vector<TexturePtr> textures, std::vector<std::string> keys);
    void removeTextureFromCache(TexturePtr tex);
    void removeTextureForKey(std::string key);
    TexturePtr getTextureForKey(std::string key);
    void cleanTextureCache();
    void removeUnusedTextures();
};


#endif /* EngineHelper_hpp */
