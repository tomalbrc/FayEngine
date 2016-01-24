//
//  Window.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Window.hpp"
#include "Scene.hpp"
#include "EngineHelper.hpp"

#define SCREEN_FPS desiredFPS
#define SCREEN_TICKS_PER_FRAME (1000/SCREEN_FPS)

Window::~Window() {
    currentScene = NULL;
}

WindowPtr Window::create(std::string wname, Vec2 size, bool fullscreen) {
    WindowPtr o(new Window());
    o->init(wname, size, fullscreen);
    return o;
}


bool Window::init(std::string wname, Vec2 size, bool fullscreen) {
    sdlWindow = SDL_CreateWindow(wname.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, fullscreen ? SDL_WINDOW_FULLSCREEN : 0); // Create window with title, position & sitze
    if (sdlWindow == nullptr) {
        FELog("SDL_CreateWindow Error: " << SDL_GetError());
        return false;
    }
    
    renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    
    EngineHelper::getInstance()->setRenderer(renderer);
    
    return true;
}

// hacky little C helper function
inline Vec2 getMouseCoords() {
    int x,y;
    SDL_GetMouseState(&x, &y);
    return Vec2Make(x,y);
}


void Window::presentScene(ScenePtr pnewScene) {
    if (currentScene) m_bShowNew = true, newScene = pnewScene;
    else newScene = pnewScene;
    
}

SDL_Renderer* Window::getRenderer() {
    return renderer;
}

Vec2 Window::getSize() {
    int w,h;
    SDL_GetWindowSize(sdlWindow, &w, &h);
    return Vec2Make(w,h);
}



ScenePtr Window::getCurrentScene() {
    return currentScene;
}



void Window::startLoop() {
    std::vector<int> countedTicks;
    int capTimer = 0;
    
    while (isRunning()) {
        capTimer = SDL_GetTicks();
        
        handleEvents();
        update();
        render();
        
        int frameTicks = SDL_GetTicks() - capTimer;
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
        
        countedTicks.push_back(SDL_GetTicks() - capTimer);
        if (countedTicks.size() >= 30) //
            countedTicks.erase(std::remove(countedTicks.begin(), countedTicks.end(), countedTicks[0]), countedTicks.end());
        
        int avgFPS = 0;
        for (int n : countedTicks) avgFPS += n;
        framerate = 1000.0/(avgFPS/(double)countedTicks.size());
        
        
        if (currentScene == nullptr || m_bShowNew) {
            currentScene = NULL;
            m_bShowNew = false;
            
            newScene->setWindow(this);
            currentScene = newScene;
            newScene = NULL;
        }
    }
}


void Window::handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                SDL_DestroyWindow(sdlWindow);
                SDL_DestroyRenderer(renderer);
                running = false;
                FELog("Event SDL_QUIT... Bye!");
                break;
            case SDL_KEYDOWN:
                if (currentScene != nullptr) currentScene->keyDown(event.key);
                break;
            case SDL_KEYUP:
                if (currentScene != nullptr) currentScene->keyUp(event.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (currentScene != nullptr) currentScene->mouseClickBegan(event.button, getMouseCoords());
                break;
            case SDL_MOUSEMOTION:
                if (currentScene != nullptr) currentScene->mouseMoved(event.motion, getMouseCoords());
                break;
            case SDL_MOUSEBUTTONUP:
                if (currentScene != nullptr) currentScene->mouseClickEnded(event.button, getMouseCoords());
                break;
            default: break;
        }
    }
}

void Window::update() {
    if (currentScene != nullptr && !currentScene->isPaused()) currentScene->update();
}
void Window::render() {
    if (currentScene != nullptr) currentScene->render();
}

void Window::quit() {
    SDL_DestroyWindow(sdlWindow);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();
    exit(0);
}

bool Window::isRunning() {
    return running;
}


