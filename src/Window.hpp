//
//  Window.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <memory>
#include "Node.hpp"

class Scene;
class Window;
typedef std::shared_ptr<Window> WindowPtr;

/**
 * Window containing a Scene.
 * The Window class handles interctions and redirects them to the currently presented Scene (if available)
 */
class Window { // TODO: m prefix
public:
    static WindowPtr create(std::string wname, Vec2 size, bool fullscreen);
    ~Window();
    
    /**
     * @return the currently presented Scene
     */
    ScenePtr getCurrentScene();
    
    /**
     * Presents a new Scene. update() and other interaction functions will be called on the Scene.
     */
    void presentScene(ScenePtr newScene);
    
    /**
     * Current framerate
     */
    double framerate = 0;
    
    /**
     * Desired framerate
     */
    int desiredFPS = 60;
    
    /**
     * Pointer to the SDL_Renderer
     */
    SDL_Renderer *getRenderer();
    
    /**
     * @return the size of the Window
     */
    Vec2 getSize();
    
    /**
     * Starts the main Game-Loop (handle events,update,render, repeat until isRunning == false)
     */
    void startLoop();
    
    /**
     * Closes the window – Quits the Game/App
     */
    void quit();
    
    /**
     * @return true if the Game-Loop is still running, false otherwise.
     */
    bool isRunning();
    
    
protected:
    bool init(std::string wname, Vec2 size, bool fullscreen);
private:
    bool m_bShowNew = false;
    SDL_Window *sdlWindow = NULL;
    SDL_Renderer *renderer = NULL;
    ScenePtr currentScene = NULL;
    ScenePtr newScene = NULL;
    bool running = true;
    
    void handleEvents();
    void update();
    void render();
};

#endif /* Window_hpp */
