//
//  Scene.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
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



void Scene::setPaused(bool flag) {
    m_bPaused = flag;
}

bool Scene::isPaused() {
    return m_bPaused;
}



void Scene::update() {
    if (!isPaused()) Node::update();
}

void Scene::render() {
    SDL_RenderClear(getWindow()->getRenderer());
    SDL_SetRenderDrawColor(getWindow()->getRenderer(), getBackgroundColor().r, getBackgroundColor().g, getBackgroundColor().b, getBackgroundColor().a);
    Node::render(getWindow()->getRenderer());
    SDL_RenderPresent(getWindow()->getRenderer());
}


FE_NAMESPACE_END
