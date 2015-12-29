//
//  Scene.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Node.hpp"
#include "Window.hpp"

class Scene;
typedef std::shared_ptr<Scene> ScenePtr;

class Scene : public Node {
public:
    static ScenePtr create();
    virtual ~Scene();
    
    virtual void setWindow(Window *window);
    Window *getWindow(void);
    
    // Render funktion, kommnt von node
    virtual void render();
    
    void setShowCursor(bool show);
    
protected:
    Scene();
    bool init();
    bool shouldBeRemoved = false;
private:
    Window *window;
};

#endif /* Scene_hpp */
