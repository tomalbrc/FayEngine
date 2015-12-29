//
//  Scene.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Scene.hpp"
#include "Sprite.hpp"

bool Scene::init() {
    return Node::init();
}

ScenePtr Scene::create() {
    return ScenePtr(new Scene());
}


Scene::Scene() {
    
}

Scene::~Scene() {
    Logbuch("DESTROY SCENE.");
    //EngineHelper::getInstance()->removeUnusedTextures();
}

void Scene::setWindow(Window *win) {
    window = win;
}
Window* Scene::getWindow(void) {
    return window;
}

void Scene::setShowCursor(bool show) {
    SDL_ShowCursor(show ? SDL_ENABLE : SDL_DISABLE);
}


void Scene::render() {
    SDL_RenderClear(window->getRenderer());
    Node::render(getWindow()->getRenderer());
    SDL_RenderPresent(window->getRenderer());
}

