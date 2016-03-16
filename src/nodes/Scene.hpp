//
//  Scene.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Node.hpp"
#include "Window.hpp"

class Scene;
typedef std::shared_ptr<Scene> ScenePtr;
typedef std::weak_ptr<Scene> SceneWeakPtr;

/**
 * Scene Class
 */
class Scene : public Node {
public:
    /**
     * Creates a new Scene object
     *
     * @return a shared_ptr to the new Scene instance
     */
    static ScenePtr create();
    
    /**
     * Deconstructor
     */
    virtual ~Scene();
    
    /**
     * Sets the background Color for the Scene
     *
     * @param new background Color
     */
    void setBackgroundColor(Color backgroundColor);
    
    /**
     * The current background Color for the Scene
     *
     * @return current background Color
     */
    Color getBackgroundColor();
    
    /**
     * Sets a new window. Normally called when presenting a new Scene
     *
     * @param window new Window
     */
    virtual void setWindow(WindowPtr window);
    
    /**
     * The current window the scene is presented in
     *
     * @return current window
     */
    WindowPtr getWindow();
    
    /**
     * Re-implement the render function from Node
     */
    virtual void render();
    
    /**
     * Set if the cursor should be shown or not
     *
     * @param flag to set wether to show or hide the cursor
     */
    void setShowCursor(bool show);
    
    /**
     * Pause the Scene
     */
    void setPaused(bool flag);
    
    /**
     * Returns true if the Scene is paused, false otherwise
     */
    bool isPaused();
    
    /**
     * Re-implementation of Node::update()
     */
    virtual void update();
    
    
protected:
    Scene();
    bool init();
    bool shouldBeRemoved = false;
private:
    Color mBackgroundColor;
    bool m_bPaused = false;
    WindowPtr window;
};

#endif /* Scene_hpp */
