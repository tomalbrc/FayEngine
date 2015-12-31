//
//  Window.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <memory>
#include "Node.hpp"

class Scene;
class Window;
typedef std::shared_ptr<Window> WindowPtr;

class Window { // TODO: m prefix
    SDL_Window *sdlWindow = NULL;
    SDL_Renderer *renderer = NULL;
    ScenePtr currentScene = NULL;
    ScenePtr newScene = NULL;
    bool running = true;
    
    void handleEvents();
    void update();
    void render();
public:
    static WindowPtr create(std::string wname, Vec2 size, bool fullscreen);
    ~Window();
    
    // Gibt die momentan angezeigte Scene zurück
    ScenePtr getCurrentScene();
    
    // Präsentiert eine neue Scene im Window (Szene im Fenster)
    void presentScene(ScenePtr newScene);
    
    // TODO: Add with getter,setter
    double framerate = 0;
    int desiredFPS = 60;
    
    SDL_Renderer *getRenderer();
    Vec2 getSize();
    
    void startLoop();
    void quit();
    
    // wirld auf false gesetzt wenn SDL_Quit oder/bzw wenn quit() aufgerufen wurde.
    bool isRunning();
    
    
protected:
    bool init(std::string wname, Vec2 size, bool fullscreen);
private:
    bool m_bShowNew = false;
};

#endif /* Window_hpp */
