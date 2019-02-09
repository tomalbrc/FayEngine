//
//  engine_helper.hpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//  
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
#include "app_window.hpp"
#include "texture.hpp"
#include "types.hpp"

RKT_NAMESPACE_BEGIN

/**
 * Helper Class. Like the CCDirector in cocos2d
 * Provides a texture Cache and save(), load() functions. Also holds a reference to SDL's 
 * renderer and a main window.
 */
class engine_helper {
public:
    /**
     * Creates (if necessary) and returns a shared instance of engine_helper.
     *
     * @return 	Pointer to an instance of engine_helper
     */
    static engine_helper *getInstance();
    
    /**
     * Returns the SDL_Renderer for the app_window.
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
    vec2f getDiplaySize();
    
    /**
     * Cache a texture in a Map
     *
     * @param	texture 	texture to cache
     * @param	key         Key for the texture
     */
    void cacheTexture(texture_ptr texture, std::string key);
    
    /**
     * Cache multiple textures for multiple keys. Both vectors should be the same size, anything else throws an exception
     *
     * @param	textures 	Textures to cache
     * @param	keys		Number of rows for the matrix
     */
    void cacheTextures(std::vector<texture_ptr> textures, std::vector<std::string> keys);
    
    /**
     * Removes a texture from the texture cache
     *
     * @param	texture		texture to remove
     */
    void removeTextureFromCache(texture_ptr texture);
    
    /**
     * Removes a texture for a key from the texture cache
     *
     * @param	key         Key for the texture to remove
     */
    void removeTextureForKey(std::string key);
    
    /**
     * Returns a texture for a specified key
     *
     * @param	key         Key for a texture
     * @return 	shared pointer to a texture instance
     */
    texture_ptr getTextureForKey(std::string key);
    
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
     * See types.hpp for available FilteringModes
     */
    void setGlobalFilteringMode(FilteringMode mode);
    
    /**
     * Returns the current filtering mode for the (main-)renderer
     */
    FilteringMode getGlobalFilteringMode();
    
    /**
     * Registers an app in order to save via engine_helper::save()
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
    void setMainWindow(app_window_ptr);
    
    /**
     * Returns the current main window (if any) for the Application
     */
    app_window_ptr getMainWindow();
    
private:
    app_window_ptr m_mainWindow;
    std::string m_basePath;
    FilteringMode m_filteringMode = FilteringModeNearest;
    engine_helper();
    ~engine_helper();
    SDL_Renderer *m_gameRenderer;
    std::map<std::string, texture_ptr> m_textureCache;
    
    bool m_initiated = false;
};

RKT_NAMESPACE_END
#endif /* EngineHelper_hpp */
