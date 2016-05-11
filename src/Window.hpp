//
//  Window.hpp
//  FayEngine
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

struct SceneTransition {
    double duration = 0.17;
    Color color = ColorBlackColor();
    EasingFunction startEasingFunction = EasingFunctionQuadEaseOut;
    EasingFunction endEasingFunction = EasingFunctionQuadEaseIn;
};
inline SceneTransition SceneTransitionMake(double duration, Color col, EasingFunction startEasingFunction, EasingFunction endEasingFunction) {
    SceneTransition transition;
    transition.color = col;
    transition.duration = duration;
    transition.startEasingFunction = startEasingFunction;
    transition.endEasingFunction = endEasingFunction;
    return transition;
}

class Scene;
class Window;
FE_create_Ptr(Window);

/**
 * Window containing a Scene.
 * The Window class handles interactions and redirects them to the currently presented Scene (if available).
 * The Scene (and all other class deriving from Scene) will also call the appropriate function to it's children nodes.
 */
class Window : public std::enable_shared_from_this<Window> { // TODO: m prefix // NAMING CONVENTION(S)  :~|
public:
    static WindowPtr create(std::string wname, Vec2 size);
    static WindowPtr create(std::string wname, Vec2 size, bool fullscreen);
    static WindowPtr create(std::string wname, Vec2 size, bool fullscreen, bool hidpi);
    ~Window();
    
    /**
     * @return the currently presented Scene
     */
    ScenePtr getCurrentScene();
    
    /**
     * Presents a new Scene with a default SceneTransition struct. update() and other interaction functions will be called on the Scene.
     */
    void presentScene(ScenePtr newScene);
    
    /**
     * Presents a new Scene. update() and other interaction functions will be called on the Scene.
     */
    void presentScene(ScenePtr newScene, SceneTransition transition);
    
    
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
    
    /**
     * @return The current screen scale (1x, 2x (HiDPI), ...)
     */
    double screenScale();
    
    
    
protected:
    bool init(std::string wname, Vec2 size, bool fullscreen, bool hidpi);
private:
    bool m_bShowNew = false;
    SDL_Window *sdlWindow = NULL;
    SDL_Renderer *renderer = NULL;
    ScenePtr currentScene = NULL;
    ScenePtr newScene = NULL;
    bool running = true;
    
    NodePtr overlay;
    
    void handleEvents();
    void update();
    void render();
    
    Vec3 accelData = Vec3Null();
    
    SceneTransition m_nextTransition;
};

#endif /* Window_hpp */
