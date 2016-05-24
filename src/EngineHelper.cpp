//
//  EngineHelper.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "EngineHelper.hpp"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "Texture.hpp"
#include <fstream>

FE_NAMESPACE_BEGIN

EngineHelper::EngineHelper() {
    FELog("EngineHelper::EngineHelper()");
}
EngineHelper::~EngineHelper() {
    FELog("EngineHelper::~EngineHelper");
    SDL_JoystickClose(0);
    cleanTextureCache();
    
    SDL_DestroyRenderer(m_gameRenderer);
    SDL_DestroyWindow(SDL_GL_GetCurrentWindow());
    
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
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


WindowPtr EngineHelper::getMainWindow() {
    return m_mainWindow;
}
void EngineHelper::setMainWindow(WindowPtr window) {
    m_mainWindow = window;
}


void EngineHelper::Init() {
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
    
    if (SDLNet_Init() == -1) {
        printf("SDLNet_Init Error: %s\n", SDLNet_GetError());
        exit(2);
    }
    
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
        printf("Mix_Init Error: %s\n", Mix_GetError());
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




void EngineHelper::cacheTexture(TexturePtr texture, std::string key) {
    m_textureCache[key] = texture;
}
void EngineHelper::cacheTextures(std::vector<TexturePtr> textures, std::vector<std::string> keys) {
    for (int i = 0; i < textures.size(); i++) {
        cacheTexture(textures[i], keys[i]);
    }
}
void EngineHelper::removeTextureForKey(std::string key) {
    m_textureCache.erase(key);
}
void EngineHelper::removeTextureFromCache(TexturePtr tex) {
    for (auto&& iterator = m_textureCache.begin(); iterator != m_textureCache.end(); ++iterator) {
        if (iterator->second == tex)  {
            removeTextureForKey(iterator->first);
            break;
        }
    }
}
TexturePtr EngineHelper::getTextureForKey(std::string key) {
    return m_textureCache[key];
}
void EngineHelper::cleanTextureCache() {
    for(auto&& iterator = m_textureCache.begin(); iterator != m_textureCache.end();) {
        FELog("Cleaning up Texture named: "<<iterator->first<<"...");
        iterator = m_textureCache.erase(iterator);
    }
}

void EngineHelper::removeUnusedTextures() {
    for(auto&& iterator = m_textureCache.begin(); iterator != m_textureCache.end();) {
        if (iterator->second.use_count() == 1) FELog("Removed unused Texture named: "<<iterator->first), iterator = m_textureCache.erase(iterator);
        else ++iterator;
    }
}



void EngineHelper::registerApp(std::string organizationName, std::string appName) {
    m_basePath = SDL_GetPrefPath(organizationName.c_str(), appName.c_str());
    FELog("Registered Application: "<<appName<<", pref base path is: "<<m_basePath);
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


} // namespace FE
