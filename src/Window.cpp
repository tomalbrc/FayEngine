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

#define CONTROLLER_AXIS_INPUT_RANGE 32767.f

FE_NAMESPACE_BEGIN

static bool FEWindowBackgrounded = false;
static SpritePtr FEWindowOverlay;

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



int EventFilter(void* userData, SDL_Event *event) {
        Window *win = (Window* )userData;
        
        switch (event->type) {
            case SDL_APP_WILLENTERBACKGROUND: {
                FEWindowBackgrounded = true;
                FELog("Will enter background " << event->type);
                if (win != NULL && win->getCurrentScene() != nullptr) win->getCurrentScene()->applicationWillEnterBackground();
                return 0;
                break;
            }
            case SDL_APP_WILLENTERFOREGROUND: {
                FEWindowBackgrounded = false;
                FELog("Will enter foreground");
                if (win != NULL && win->getCurrentScene() != nullptr) win->getCurrentScene()->applicationWillEnterForeground();
                return 0;
                break;
            }
            case SDL_APP_DIDENTERFOREGROUND: {
                FEWindowBackgrounded = false;
                if (win != NULL && win->getCurrentScene() != nullptr) win->getCurrentScene()->applicationDidEnterForeground();
                return 0;
                break;
            }
            case SDL_APP_DIDENTERBACKGROUND: {
                FEWindowBackgrounded = true;
                if (win != NULL && win->getCurrentScene() != nullptr) win->getCurrentScene()->applicationDidEnterBackground();
                return 0;
                break;
            }
            default: break;
        }
    return 1;
}
bool Window::init(std::string wname, Vec2 size, bool fullscreen, bool hidpi) {
    FE::EngineHelper::getInstance()->Init();
    
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
    
    SDL_SetEventFilter(EventFilter, this);
    
    EngineHelper::getInstance()->setRenderer(renderer);
    EngineHelper::getInstance()->setMainWindow(shared_from_this());
    
    SDL_GameControllerOpen(0);
    
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
        if (!FEWindowBackgrounded) update(), render();
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
        } else if ((m_bShowNew && (FEWindowOverlay.get() == nullptr || (FEWindowOverlay.get() != nullptr && FEWindowOverlay->getParent() == nullptr)))) { // TODO: Add Transition between scenes
            FEWindowOverlay.reset();
            FEWindowOverlay = Sprite::create(Texture::create(getSize(), m_nextTransition.color));
            FEWindowOverlay->setAlpha(0);
            FEWindowOverlay->setZPosition(__FLT_MAX__);
            currentScene->addChild(FEWindowOverlay);
            
            auto fade = FadeAlphaToAction::create(m_nextTransition.duration, 255);
            fade->setEasingFunction(m_nextTransition.startEasingFunction);
            FEWindowOverlay->runAction(SequenceAction::create({
                fade,
            }), "o");
            
            m_bShowNew = false;
        } else if (FEWindowOverlay.get() != nullptr && FEWindowOverlay->getAction("o") == nullptr && newScene != nullptr) {
            
            currentScene.reset();
            currentScene = newScene;
            currentScene->setWindow(this->shared_from_this());
            newScene.reset();
            
            FEWindowOverlay->removeFromParent();
            currentScene->addChild(FEWindowOverlay);
            
            auto fade = FadeAlphaToAction::create(m_nextTransition.duration, 0);
            fade->setEasingFunction(m_nextTransition.endEasingFunction);
            FEWindowOverlay->runAction(SequenceAction::create({
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
                if (event.jaxis.axis == 0) accelData.x = event.jaxis.value / CONTROLLER_AXIS_INPUT_RANGE * 5.f;
                if (event.jaxis.axis == 1) accelData.y = event.jaxis.value / CONTROLLER_AXIS_INPUT_RANGE * 5.f;
                if (event.jaxis.axis == 2) accelData.z = event.jaxis.value / CONTROLLER_AXIS_INPUT_RANGE * 5.f;
                if (currentScene != nullptr) currentScene->accelerometerMoved(accelData);
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
                FELog("CONTROLLERDEVICEADDED");
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
                if (currentScene != nullptr) currentScene->controllerAxisMotion(event.cdevice.which, (SDL_GameControllerAxis)event.caxis.axis, event.caxis.value/CONTROLLER_AXIS_INPUT_RANGE);
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
