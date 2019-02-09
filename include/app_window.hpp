//
//  app_window.hpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//  
//

#ifndef Window_hpp
#define Window_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <memory>
#include "node.hpp"

RKT_NAMESPACE_BEGIN

struct SceneTransition {
    double duration = 0.17;
    color4u color = ColorBlackColor();
    EasingFunction startEasingFunction = EasingFunctionQuadEaseOut;
    EasingFunction endEasingFunction = EasingFunctionQuadEaseIn;
};

inline SceneTransition SceneTransitionMake(double duration, color4u col, EasingFunction startEasingFunction, EasingFunction endEasingFunction) {
    SceneTransition transition;
    transition.color = col;
    transition.duration = duration;
    transition.startEasingFunction = startEasingFunction;
    transition.endEasingFunction = endEasingFunction;
    return transition;
}

class scene;
class app_window;
RKT_create_ptr(app_window);

/**
 * app_window containing a scene.
 * The app_window class handles interactions and redirects them to the currently presented scene (if available).
 * The scene (and all other class deriving from scene) will also call the appropriate function to it's children nodes.
 */
class app_window : public std::enable_shared_from_this<app_window> { // TODO: m prefix // NAMING CONVENTION(S)  :~|
public:
    static app_window_ptr create(std::string wname, vec2f size);
    static app_window_ptr create(std::string wname, vec2f size, bool fullscreen);
    static app_window_ptr create(std::string wname, vec2f size, bool fullscreen, bool hidpi);
    ~app_window();
    
    /**
     * @return the currently presented scene
     */
    scene_ptr getCurrentScene();
    
    /**
     * Presents a new scene with a default SceneTransition struct. update() and other interaction functions will be called on the scene.
     */
    void presentScene(scene_ptr newScene);
    
    /**
     * Presents a new scene. update() and other interaction functions will be called on the scene.
     */
    void presentScene(scene_ptr newScene, SceneTransition transition);
    
    
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
     * @return the size of the app_window
     */
    vec2f getSize();
    
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
    bool init(std::string wname, vec2f size, bool fullscreen, bool hidpi);
private:
    bool m_showNew = false;
    SDL_Window *m_sdlWindow = NULL;
    SDL_Renderer *m_renderer = NULL;
    scene_ptr m_currentScene = NULL;
    scene_ptr m_newScene = NULL;
    bool m_running = true;
    
    void handleEvents();
    void update();
    void render();
    
    vec3f m_accelData = Vec3Null();
    
    SceneTransition m_nextTransition;
    
    float m_screenScale = -1.f;
};

RKT_NAMESPACE_END
#endif /* Window_hpp */
