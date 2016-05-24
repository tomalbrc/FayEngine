//
//  EngineHelper.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef EngineHelper_hpp
#define EngineHelper_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "tmxparser.h"
#include "Window.hpp"
#include "Texture.hpp"


FE_NAMESPACE_BEGIN

/**
 * Helper Class. Like the CCDirector in cocos2d
 * Provides a Texture Cache and save(), load() functions. Also holds a reference to the renderer and main window.
 */
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
     * virtual initiates SDL, SDL_image and SDL_ttf
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
     * Cache a texture in a Map
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
    
    /**
     * Sets the filtering mode for the renderer.
     * The filtering mode is checked when a texture is created and also affects copied textures
     * See Types.hpp for available FilteringModes
     */
    //void setGlobalFilteringMode(FilteringMode mode);
    
    /**
     * Returns the current filtering mode for the (main-)renderer
     */
    //FilteringMode getGlobalFilteringMode();
    
    /**
     * Registers an app in order to save via EngineHelper::save()
     *
     * @param organizationName  name e.g. 'My Company'
     * @param appName           name e.g. 'My App'
     */
    void registerApp(std::string organizationName, std::string appName);
    
    
    /**
     * Saves a string for a key. The key is used as filename and '.bin' is appended. The location is SDL_GetPrefPath()
     *
     * @param string            string to save
     * @param key               key to save the string for
     */
    void save(std::string string, std::string key);
    
    /**
     * Loads a string for a specified key
     */
    std::string loadString(std::string key);
    
    /**
     * Saves a double for a key. The key is used as filename and '.bin' is appended. The location is SDL_GetPrefPath()
     *
     * @param value             double to save
     * @param key               key to save the double for
     */
    void save(double value, std::string key);
    
    /**
     * Loads a double for a specified key
     */
    double loadDouble(std::string key);
    
    /**
     * Saves an int for a key. The key is used as filename and '.bin' is appended. The location is SDL_GetPrefPath()
     *
     * @param value             int to save
     * @param key               key to save the int for
     */
    void save(int value, std::string key);
    
    /**
     * Loads an int for a specified key
     */
    int loadInt(std::string key);
    
    /**
     * Sets the main window for the Application
     */
    void setMainWindow(WindowPtr);
    
    /**
     * Returns the current main window (if any) for the Application
     */
    WindowPtr getMainWindow();
    
    
private:
    WindowPtr m_mainWindow;
    std::string m_basePath;
    EngineHelper();
    ~EngineHelper();
    SDL_Renderer *m_gameRenderer;
    std::map<std::string, TexturePtr> m_textureCache;
};

FE_NAMESPACE_END
#endif /* EngineHelper_hpp */
