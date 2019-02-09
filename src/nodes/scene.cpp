//
//  scene.cpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//  
//

#include "scene.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

bool scene::init() {
    return node::init();
}

scene_ptr scene::create() {
    return scene_ptr(new scene());
}


scene::scene() {
    mBackgroundColor = ColorBlackColor();
}

scene::~scene() {
    
}



void scene::setBackgroundColor(color4u backgroundColor) {
    mBackgroundColor = backgroundColor;
}
color4u scene::getBackgroundColor(void) {
    return mBackgroundColor;
}



void scene::setWindow(app_window_ptr win) {
    window = win;
}
app_window_ptr scene::getWindow(void) {
    return window;
}

void scene::setShowCursor(bool show) {
    SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
}





void scene::update() {
    node::update();
}

void scene::render() {
    SDL_RenderClear(getWindow()->getRenderer());
    SDL_SetRenderDrawColor(getWindow()->getRenderer(), getBackgroundColor().r, getBackgroundColor().g, getBackgroundColor().b, getBackgroundColor().a);
    node::render(getWindow()->getRenderer());
    SDL_RenderPresent(getWindow()->getRenderer());
}





void scene::orientationChange(DeviceOrientation newOrientation) {
    
}

void scene::applicationWillEnterForeground() {
    
}

void scene::applicationDidEnterForeground() {
    
}

void scene::applicationWillEnterBackground() {
    
}

void scene::applicationDidEnterBackground() {
    
}




RKT_NAMESPACE_END
