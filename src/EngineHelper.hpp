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
public:
    /**
     * Creates (if necessary) and returns a shared instance of EngineHelper.
     *
     * @return 	Pointer to an instance of EngineHelper
     */
    static EngineHelper *getInstance();
    
    /**
     * Returns the SDL_Renderer for the Window.
     *
     * @return 	Pointer to an SDL_Renderer
     */
    SDL_Renderer* getRenderer();
    
    /**
     * Sets a Pointer to an SDL_Renderer
     *
     * @param	renderer 	A valid SDL_Renderer
     */
    void setRenderer(SDL_Renderer *renderer);
    
    /**
     * Initiates SDL, SDL_image and SDL_ttf
     */
    void Init();
    
    /**
     * Enables or disables vsync for the Application (Game)
     *
     * @param	enable      flag to enable/disable vsync
     */
    void setEnableVSync(bool enable);
    
    /**
     * Returns the current pixel size in pixels
     *
     * @return 	The current display size in pixels
     */
    Vec2 getDiplaySize();
    
    /**
     * Cache a texture in an std::map
     *
     * @param	texture 	Texture to cache
     * @param	key         Key for the texture
     */
    void cacheTexture(TexturePtr texture, std::string key);
    
    /**
     * Cache multiple textures for multiple keys. Both vectors should be the same size, anything else throws an exception
     *
     * @param	textures 	Textures to cache
     * @param	keys		Number of rows for the matrix
     */
    void cacheTextures(std::vector<TexturePtr> textures, std::vector<std::string> keys);
    
    /**
     * Removes a texture from the texture cache
     *
     * @param	texture		Texture to remove
     */
    void removeTextureFromCache(TexturePtr texture);
    
    /**
     * Removes a texture for a key from the texture cache
     *
     * @param	key         Key for the Texture to remove
     */
    void removeTextureForKey(std::string key);
    
    /**
     * Returns a texture for a specified key
     *
     * @param	key         Key for a Texture
     * @return 	shared pointer to a Texture instance
     */
    TexturePtr getTextureForKey(std::string key);
    
    /**
     * Removes every texture from the cache
     */
    void cleanTextureCache();
    
    /**
     * Removes every unused texture (whose shared_ptr's use_count equals 1) from the cache
     */
    void removeUnusedTextures();
    
    
    
private:
    EngineHelper();
    ~EngineHelper();
    SDL_Renderer *gameRenderer;
    std::map<std::string, TexturePtr> textureCache;
};


#endif /* EngineHelper_hpp */
