//
//  Scene.cpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//  
//

#include "Scene.hpp"
#include "Sprite.hpp"

FE_NAMESPACE_BEGIN

bool Scene::init() {
    return Node::init();
}

ScenePtr Scene::create() {
    return ScenePtr(new Scene());
}


Scene::Scene() {
    mBackgroundColor = ColorBlackColor();
}

Scene::~Scene() {
    
}



void Scene::setBackgroundColor(Color backgroundColor) {
    mBackgroundColor = backgroundColor;
}
Color Scene::getBackgroundColor(void) {
    return mBackgroundColor;
}



void Scene::setWindow(WindowPtr win) {
    window = win;
}
WindowPtr Scene::getWindow(void) {
    return window;
}

void Scene::setShowCursor(bool show) {
    SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
}





void Scene::update() {
    Node::update();
}

void Scene::render() {
    SDL_RenderClear(getWindow()->getRenderer());
    SDL_SetRenderDrawColor(getWindow()->getRenderer(), getBackgroundColor().r, getBackgroundColor().g, getBackgroundColor().b, getBackgroundColor().a);
    Node::render(getWindow()->getRenderer());
    SDL_RenderPresent(getWindow()->getRenderer());
}





void Scene::orientationChange(DeviceOrientation newOrientation) {
    
}

void Scene::applicationWillEnterForeground() {
    
}

void Scene::applicationDidEnterForeground() {
    
}

void Scene::applicationWillEnterBackground() {
    
}

void Scene::applicationDidEnterBackground() {
    
}




FE_NAMESPACE_END
