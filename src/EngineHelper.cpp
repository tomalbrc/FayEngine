//
//  EngineHelper.cpp
//  PixelDead_SDL
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

EngineHelper::EngineHelper() {
    FELog("EngineHelper::EngineHelper()");
}
EngineHelper::~EngineHelper() {
    cleanTextureCache();
    FELog("EngineHelper::~EngineHelper");
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_JoystickClose(0);
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
    for(auto&& iterator = textureCache.begin(); iterator != textureCache.end();) {
        FELog("Cleaning up Texture named: "<<iterator->first<<"...");
        iterator = textureCache.erase(iterator);
    }
}

void EngineHelper::removeUnusedTextures() {
    for(auto&& iterator = textureCache.begin(); iterator != textureCache.end();) {
        if (iterator->second.use_count() == 1) FELog("Removed unused Texture named: "<<iterator->first), iterator = textureCache.erase(iterator);
        else ++iterator;
    }
}



void EngineHelper::registerApp(std::string organizationName, std::string appName) {
    basePath = SDL_GetPrefPath(organizationName.c_str(), appName.c_str());
    FELog("Registered "<<appName<<", pref base path is: "<<basePath);
}


/**
 * Saves an object for a key. The key is used as filename and '.bin' is appended. The location is SDL_GetPrefPath()
 */
void EngineHelper::save(std::string string, std::string key) {
    auto path = (basePath + key + ".bin").c_str();
    std::ofstream file (path, std::ofstream::binary);
    file << string, file.close(); // close() not necessairy since ofstream will be handled automatically if out of scope
}
std::string EngineHelper::loadString(std::string key) {
    std::ifstream file(basePath + key + ".bin", std::ifstream::binary);
    std::string out;
    file >> out;
    return out;
}

void EngineHelper::save(double value, std::string key) {
    auto path = (basePath + key + ".bin").c_str();
    std::ofstream file (path, std::ofstream::binary);
    file << value, file.close();
}
double EngineHelper::loadDouble(std::string key) {
    std::ifstream file(basePath + key + ".bin", std::ifstream::binary);
    std::string out;
    file >> out;
    return out.empty() ? 0.0 : std::stod(out);
}

void EngineHelper::save(int value, std::string key) {
    auto path = (basePath + key + ".bin").c_str();
    std::ofstream file (path, std::ofstream::binary);
    file << value, file.close();
}
int EngineHelper::loadInt(std::string key) {
    std::ifstream file(basePath + key + ".bin", std::ifstream::binary);
    std::string out;
    file >> out;
    return out.empty() ? 0 : std::stoi(out);
}
