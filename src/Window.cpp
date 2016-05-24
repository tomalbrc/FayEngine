//
//  Window.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Window.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"
#include "SequenceAction.hpp"
#include "WaitAction.hpp"
#include "FadeAlphaToAction.hpp"
#include "RemoveFromParent.hpp"
#include "EngineHelper.hpp"

#define SCREEN_FPS desiredFPS
#define SCREEN_TICKS_PER_FRAME (1000/SCREEN_FPS)

FE_NAMESPACE_BEGIN

static SpritePtr overlay;

Window::~Window() {
    currentScene = NULL;
}

WindowPtr Window::create(std::string wname, Vec2 size) {
    return create(wname, size, false);
}

WindowPtr Window::create(std::string wname, Vec2 size, bool fullscreen) {
    return create(wname, size, false, false);
}
WindowPtr Window::create(std::string wname, Vec2 size, bool fullscreen, bool hidpi) {
    WindowPtr o(new Window());
    o->init(wname, size, fullscreen, hidpi);
    return o;
}




bool Window::init(std::string wname, Vec2 size, bool fullscreen, bool hidpi) {
    Uint32 flags = hidpi ? SDL_WINDOW_ALLOW_HIGHDPI : 0;
    flags |= SDL_WINDOW_SHOWN;
#if defined(TARGET_OS_IOS) && TARGET_OS_IOS == 1
    flags |= SDL_WINDOW_BORDERLESS;
#endif
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    sdlWindow = SDL_CreateWindow(wname.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, flags); // Create window with title, position & sitze
    if (sdlWindow == nullptr) {
        FELog("SDL_CreateWindow Error: " << SDL_GetError());
        return false;
    }
    
    renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    EngineHelper::getInstance()->setRenderer(renderer);
    EngineHelper::getInstance()->setMainWindow(shared_from_this());
    
    return true;
}

// hacky little C helper function
inline Vec2 getMouseCoords() {
    int x,y;
    SDL_GetMouseState(&x, &y);
    return Vec2Make(x,y);
}


void Window::presentScene(ScenePtr pnewScene) {
    SceneTransition trans;
    presentScene(pnewScene, trans);
}

void Window::presentScene(ScenePtr pnewScene, SceneTransition transition) {
    m_nextTransition = transition;
    if (currentScene != nullptr) m_bShowNew = true, newScene = pnewScene;
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
        /*
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
        */
        
        
        if (currentScene == nullptr) {
            currentScene = NULL;
            m_bShowNew = false;
            
            newScene->setWindow(this->shared_from_this());
            currentScene = newScene;
            newScene = NULL;
        } else if ((m_bShowNew && (overlay.get() == nullptr || (overlay.get() != nullptr && overlay->getParent() == nullptr)))) { // TODO: Add Transition between scenes
            overlay.reset();
            overlay = Sprite::create(Texture::create(getSize(), m_nextTransition.color));
            overlay->setAlpha(0);
            overlay->setZPosition(__FLT_MAX__);
            currentScene->addChild(overlay);
            
            auto fade = FadeAlphaToAction::create(m_nextTransition.duration, 255);
            fade->setEasingFunction(m_nextTransition.startEasingFunction);
            overlay->runAction(SequenceAction::create({
                fade,
            }), "o");
            
            m_bShowNew = false;
        } else if (overlay.get() != nullptr && overlay->getAction("o") == nullptr && newScene != nullptr) {
            
            currentScene.reset();
            currentScene = newScene;
            currentScene->setWindow(this->shared_from_this());
            newScene.reset();
            
            overlay->removeFromParent();
            currentScene->addChild(overlay);
            
            auto fade = FadeAlphaToAction::create(m_nextTransition.duration, 0);
            fade->setEasingFunction(m_nextTransition.endEasingFunction);
            overlay->runAction(SequenceAction::create({
                fade,
                RemoveFromParentAction::create(),
            }), "o2");
            
            m_bShowNew = false;
        }
    }
}


void Window::handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                FELog("Event SDL_QUIT... Bye!");
                break;
            case SDL_KEYDOWN:
                if (currentScene != nullptr) currentScene->keyDown(FEKeyCode(event.key.keysym.sym));
                break;
            case SDL_KEYUP:
                if (currentScene != nullptr) currentScene->keyUp(FEKeyCode(event.key.keysym.sym));
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
            case SDL_JOYAXISMOTION: { // ACCELEROMETER SUPPORT // TODO: Change EngineHelper's init and this to check for SDL_JoystickDeviceAdded event
                if (event.jaxis.axis == 0) accelData.x = event.jaxis.value;
                if (event.jaxis.axis == 1) accelData.y = event.jaxis.value;
                if (event.jaxis.axis == 2) {
                    accelData.z = event.jaxis.value;
                    if (currentScene != nullptr) currentScene->accelerometerMoved(accelData);
                }
                break;
            }
            case SDL_FINGERDOWN: {
                if (currentScene != nullptr) currentScene->touchBegan(event.tfinger, Vec2Make(event.tfinger.x, event.tfinger.y)*getSize());
                break;
            }
            case SDL_FINGERMOTION: {
                if (currentScene != nullptr) currentScene->touchMoved(event.tfinger, Vec2Make(event.tfinger.x, event.tfinger.y)*getSize());
                break;
            }
            case SDL_FINGERUP: {
                if (currentScene != nullptr) currentScene->touchEnded(event.tfinger, Vec2Make(event.tfinger.x, event.tfinger.y)*getSize());
                break;
            }
            
            case SDL_CONTROLLERDEVICEADDED:
                FELog("SDL_CONTROLLERDEVICEADDED");
                SDL_GameControllerOpen(event.cdevice.which);
                break;
            case SDL_CONTROLLERBUTTONDOWN: {
                if (currentScene != nullptr) currentScene->controllerPushedButton(event.cdevice.which, (SDL_GameControllerButton)event.cbutton.button);
                break;
            }
            case SDL_CONTROLLERBUTTONUP: {
                if (currentScene != nullptr) currentScene->controllerReleasedButton(event.cdevice.which, (SDL_GameControllerButton)event.cbutton.button);
                break;
            }
            case SDL_CONTROLLERAXISMOTION: {
                if (currentScene != nullptr) currentScene->controllerAxisMotion(event.cdevice.which, (SDL_GameControllerAxis)event.caxis.axis, event.caxis.value);
                break;
            }
            
            
            default: break;
        }
    }
}

void Window::update() {
    if (currentScene != nullptr) currentScene->update();
}
void Window::render() {
    if (currentScene != nullptr) currentScene->render();
}

void Window::quit() {
    running = false;
    
    SDL_DestroyWindow(sdlWindow);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit();
    exit(0);
}

bool Window::isRunning() {
    return running;
}


double Window::screenScale() {
    int x,y;
    SDL_GetWindowSize(sdlWindow, &x, &y);
    
    int w,h;
    SDL_GL_GetDrawableSize(sdlWindow, &w, &h);
    
    return w/double(x);
}


FE_NAMESPACE_END
