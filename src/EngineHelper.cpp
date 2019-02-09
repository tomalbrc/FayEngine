//
//  EngineHelper.cpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//  
//

#include "EngineHelper.hpp"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "Texture.hpp"
#include "Types.hpp" 
#include <fstream>


RKT_NAMESPACE_BEGIN

EngineHelper::EngineHelper() {
    RKTLog("EngineHelper::EngineHelper()");
}
EngineHelper::~EngineHelper() {
    RKTLog("EngineHelper::~EngineHelper");
    SDL_JoystickClose(0);
    cleanTextureCache();
    
    SDL_DestroyRenderer(m_gameRenderer);
    SDL_DestroyWindow(SDL_GL_GetCurrentWindow());
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

EngineHelper* EngineHelper::getInstance() {
    static EngineHelper theInstance;
    return &theInstance;
}



SDL_Renderer* EngineHelper::getRenderer() {
    return m_gameRenderer;
}
void EngineHelper::setRenderer(SDL_Renderer *r) {
    m_gameRenderer = r;
}


app_window_ptr EngineHelper::getMainWindow() {
    return m_mainWindow;
}
void EngineHelper::setMainWindow(app_window_ptr window) {
    m_mainWindow = window;
}


void EngineHelper::Init() {
    if (m_initiated) return;
    m_initiated = true;
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(2);
    }
    
    if(TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        exit(2);
    }
    
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == -1) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        exit(2);
    }
    
    // For ios/android
    // TODO: Add platform check
    SDL_SetHint(SDL_HINT_ACCELEROMETER_AS_JOYSTICK, "1");
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_JoystickOpen(0);
}




void EngineHelper::setEnableVSync(bool enable) {
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, enable ? "1":"0");
}

Vec2 EngineHelper::getDiplaySize() {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    return Vec2Make(mode.w, mode.h);
}




void EngineHelper::cacheTexture(Texture_ptr texture, std::string key) {
    m_textureCache[key] = texture;
}
void EngineHelper::cacheTextures(std::vector<Texture_ptr> textures, std::vector<std::string> keys) {
    for (int i = 0; i < textures.size(); i++) {
        cacheTexture(textures[i], keys[i]);
    }
}
void EngineHelper::removeTextureForKey(std::string key) {
    m_textureCache.erase(key);
}
void EngineHelper::removeTextureFromCache(Texture_ptr tex) {
    for (auto&& iterator = m_textureCache.begin(); iterator != m_textureCache.end(); ++iterator) {
        if (iterator->second == tex)  {
            removeTextureForKey(iterator->first);
            break;
        }
    }
}
Texture_ptr EngineHelper::getTextureForKey(std::string key) {
    return m_textureCache[key];
}
void EngineHelper::cleanTextureCache() {
    for(auto&& iterator = m_textureCache.begin(); iterator != m_textureCache.end();) {
        RKTLog("Cleaning up Texture named: "<<iterator->first<<"...");
        iterator = m_textureCache.erase(iterator);
    }
}

void EngineHelper::removeUnusedTextures() {
    for(auto&& iterator = m_textureCache.begin(); iterator != m_textureCache.end();) {
        if (iterator->second.use_count() == 1) RKTLog("Removed unused Texture named: "<<iterator->first), iterator = m_textureCache.erase(iterator);
        else ++iterator;
    }
}


/**
 * Sets the filtering mode for the renderer.
 * The filtering mode is checked when a texture is created and also affects copied textures
 * See Types.hpp for available FilteringModes
 */
void EngineHelper::setGlobalFilteringMode(FilteringMode mode) {
    m_filteringMode = mode;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, std::to_string(mode).c_str());
}

/**
 * Returns the current filtering mode for the (main-)renderer
 */
FilteringMode EngineHelper::getGlobalFilteringMode() {
    return m_filteringMode;
}




void EngineHelper::registerApp(std::string organizationName, std::string appName) {
    m_basePath = SDL_GetPrefPath(organizationName.c_str(), appName.c_str());
    RKTLog("Registered Application: "<<appName<<", pref base path is: "<<m_basePath);
}


/**
 * Saves an object for a key. The key is used as filename and '.bin' is appended. The location is SDL_GetPrefPath()
 */
void EngineHelper::save(std::string string, std::string key) {
    auto path = (m_basePath + key + ".bin").c_str();
    std::ofstream file (path, std::ofstream::binary);
    if (file.is_open()) file << string, file.close();
    else SDL_assert(1);
}
std::string EngineHelper::loadString(std::string key) {
    std::ifstream file(m_basePath + key + ".bin", std::ifstream::binary);
    std::string out;
    file >> out;
    return out;
}

void EngineHelper::save(double value, std::string key) {
    auto path = (m_basePath + key + ".bin").c_str();
    std::ofstream file (path, std::ofstream::binary);
    if (file.is_open()) file << value, file.close();
    else SDL_assert(1);
}
double EngineHelper::loadDouble(std::string key) {
    std::ifstream file(m_basePath + key + ".bin", std::ifstream::binary);
    std::string out;
    file >> out;
    return out.empty() ? 0.0 : std::stod(out);
}

void EngineHelper::save(int value, std::string key) {
    auto path = (m_basePath + key + ".bin").c_str();
    std::ofstream file (path, std::ofstream::binary);
    if (file.is_open()) file << value, file.close();
    else SDL_assert(1);
}
int EngineHelper::loadInt(std::string key) {
    std::ifstream file(m_basePath + key + ".bin", std::ifstream::binary);
    std::string out;
    file >> out;
    return out.empty() ? 0 : std::stoi(out);
}


RKT_NAMESPACE_END
