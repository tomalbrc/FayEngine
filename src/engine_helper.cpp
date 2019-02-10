//
//  engine_helper.cpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//  
//

#include "engine_helper.hpp"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "texture.hpp"
#include "types.hpp" 
#include <fstream>


RKT_NAMESPACE_BEGIN

engine_helper::engine_helper() {
    debug_log("engine_helper::engine_helper()");
}
engine_helper::~engine_helper() {
    debug_log("engine_helper::~engine_helper");
    SDL_JoystickClose(0);
    cleanTextureCache();
    
    SDL_DestroyRenderer(m_gameRenderer);
    SDL_DestroyWindow(SDL_GL_GetCurrentWindow());
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

engine_helper* engine_helper::getInstance() {
    static engine_helper theInstance;
    return &theInstance;
}



SDL_Renderer* engine_helper::getRenderer() {
    return m_gameRenderer;
}
void engine_helper::setRenderer(SDL_Renderer *r) {
    m_gameRenderer = r;
}


app_window_ptr engine_helper::getMainWindow() {
    return m_mainWindow;
}
void engine_helper::setMainWindow(app_window_ptr window) {
    m_mainWindow = window;
}


void engine_helper::Init() {
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




void engine_helper::setEnableVSync(bool enable) {
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, enable ? "1":"0");
}

vec2f engine_helper::getDiplaySize() {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    return vec2f_make(mode.w, mode.h);
}




void engine_helper::cacheTexture(texture_ptr texture, std::string key) {
    m_textureCache[key] = texture;
}
void engine_helper::cacheTextures(std::vector<texture_ptr> textures, std::vector<std::string> keys) {
    for (int i = 0; i < textures.size(); i++) {
        cacheTexture(textures[i], keys[i]);
    }
}
void engine_helper::removeTextureForKey(std::string key) {
    m_textureCache.erase(key);
}
void engine_helper::removeTextureFromCache(texture_ptr tex) {
    for (auto&& iterator = m_textureCache.begin(); iterator != m_textureCache.end(); ++iterator) {
        if (iterator->second == tex)  {
            removeTextureForKey(iterator->first);
            break;
        }
    }
}
texture_ptr engine_helper::getTextureForKey(std::string key) {
    return m_textureCache[key];
}
void engine_helper::cleanTextureCache() {
    for(auto&& iterator = m_textureCache.begin(); iterator != m_textureCache.end();) {
        debug_log("Cleaning up texture named: "+iterator->first+"...");
        iterator = m_textureCache.erase(iterator);
    }
}

void engine_helper::removeUnusedTextures() {
    for(auto&& iterator = m_textureCache.begin(); iterator != m_textureCache.end();) {
        if (iterator->second.use_count() == 1) debug_log("Removed unused texture named: "+iterator->first), iterator = m_textureCache.erase(iterator);
        else ++iterator;
    }
}


/**
 * Sets the filtering mode for the renderer.
 * The filtering mode is checked when a texture is created and also affects copied textures
 * See types.hpp for available FilteringModes
 */
void engine_helper::setGlobalFilteringMode(FilteringMode mode) {
    m_filteringMode = mode;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, std::to_string(mode).c_str());
}

/**
 * Returns the current filtering mode for the (main-)renderer
 */
FilteringMode engine_helper::getGlobalFilteringMode() {
    return m_filteringMode;
}




void engine_helper::registerApp(std::string organizationName, std::string appName) {
    m_basePath = SDL_GetPrefPath(organizationName.c_str(), appName.c_str());
    debug_log("Registered Application: " + appName + ", pref base path is: " + m_basePath);
}


/**
 * Saves an object for a key. The key is used as filename and '.bin' is appended. The location is SDL_GetPrefPath()
 */
void engine_helper::save(std::string string, std::string key) {
    auto path = (m_basePath + key + ".bin").c_str();
    std::ofstream file (path, std::ofstream::binary);
    if (file.is_open()) file << string, file.close();
    else SDL_assert(1);
}
std::string engine_helper::loadString(std::string key) {
    std::ifstream file(m_basePath + key + ".bin", std::ifstream::binary);
    std::string out;
    file >> out;
    return out;
}

void engine_helper::save(double value, std::string key) {
    auto path = (m_basePath + key + ".bin").c_str();
    std::ofstream file (path, std::ofstream::binary);
    if (file.is_open()) file << value, file.close();
    else SDL_assert(1);
}
double engine_helper::loadDouble(std::string key) {
    std::ifstream file(m_basePath + key + ".bin", std::ifstream::binary);
    std::string out;
    file >> out;
    return out.empty() ? 0.0 : std::stod(out);
}

void engine_helper::save(int value, std::string key) {
    auto path = (m_basePath + key + ".bin").c_str();
    std::ofstream file (path, std::ofstream::binary);
    if (file.is_open()) file << value, file.close();
    else SDL_assert(1);
}
int engine_helper::loadInt(std::string key) {
    std::ifstream file(m_basePath + key + ".bin", std::ifstream::binary);
    std::string out;
    file >> out;
    return out.empty() ? 0 : std::stoi(out);
}


RKT_NAMESPACE_END
