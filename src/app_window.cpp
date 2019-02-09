//
//  app_window.cpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//
//

#include "app_window.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "sequence_action.hpp"
#include "wait_action.hpp"
#include "fade_action.hpp"
#include "remove_action.hpp"
#include "engine_helper.hpp"

#define SCREEN_FPS desiredFPS
#define SCREEN_TICKS_PER_FRAME (1000/SCREEN_FPS)

#define CONTROLLER_AXIS_INPUT_RANGE 32767.f

RKT_NAMESPACE_BEGIN

static bool RKTWindowBackgrounded = false;
static sprite_ptr RKTWindowOverlay;

app_window::~app_window() {
    m_currentScene.reset();
}

app_window_ptr app_window::create(std::string wname, vec2f size) {
    return create(wname, size, false);
}

app_window_ptr app_window::create(std::string wname, vec2f size, bool fullscreen) {
    return create(wname, size, false, false);
}
app_window_ptr app_window::create(std::string wname, vec2f size, bool fullscreen, bool hidpi) {
    app_window_ptr o(new app_window());
    o->init(wname, size, fullscreen, hidpi);
    return o;
}



int EventFilter(void* userData, SDL_Event *event) {
        app_window *win = (app_window* )userData;
        
        switch (event->type) {
            case SDL_APP_WILLENTERBACKGROUND: {
                RKTWindowBackgrounded = true;
                RKTLog("Will enter background " << event->type);
                if (win != NULL && win->getCurrentScene() != nullptr) win->getCurrentScene()->applicationWillEnterBackground();
                return 0;
                break;
            }
            case SDL_APP_WILLENTERFOREGROUND: {
                RKTWindowBackgrounded = false;
                RKTLog("Will enter foreground");
                if (win != NULL && win->getCurrentScene() != nullptr) win->getCurrentScene()->applicationWillEnterForeground();
                return 0;
                break;
            }
            case SDL_APP_DIDENTERFOREGROUND: {
                RKTWindowBackgrounded = false;
                if (win != NULL && win->getCurrentScene() != nullptr) win->getCurrentScene()->applicationDidEnterForeground();
                return 0;
                break;
            }
            case SDL_APP_DIDENTERBACKGROUND: {
                RKTWindowBackgrounded = true;
                if (win != NULL && win->getCurrentScene() != nullptr) win->getCurrentScene()->applicationDidEnterBackground();
                return 0;
                break;
            }
            default: break;
        }
    return 1;
}
bool app_window::init(std::string wname, vec2f size, bool fullscreen, bool hidpi) {
    rkt::engine_helper::getInstance()->Init();
    
    Uint32 flags = hidpi ? SDL_WINDOW_ALLOW_HIGHDPI : 0;
    flags |= SDL_WINDOW_SHOWN;
#if defined(TARGET_OS_IOS) && TARGET_OS_IOS == 1
    flags |= SDL_WINDOW_BORDERLESS;
#endif
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    m_sdlWindow = SDL_CreateWindow(wname.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, flags); // Create window with title, position & sitze
    if (m_sdlWindow == nullptr) {
        RKTLog("SDL_CreateWindow Error: " << SDL_GetError());
        return false;
    }
    
    m_renderer = SDL_CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    
    SDL_SetEventFilter(EventFilter, this);
    
    engine_helper::getInstance()->setRenderer(m_renderer);
    engine_helper::getInstance()->setMainWindow(shared_from_this());
    
    SDL_GameControllerOpen(0);
    
    return true;
}

// hacky little C helper function
inline vec2f getMouseCoords() {
    int x,y;
    SDL_GetMouseState(&x, &y);
    return vec2f_make(x,y);
}


void app_window::presentScene(scene_ptr pnewScene) {
    SceneTransition trans;
    presentScene(pnewScene, trans);
}

void app_window::presentScene(scene_ptr pnewScene, SceneTransition transition) {
    m_nextTransition = transition;
    if (m_currentScene != nullptr) m_showNew = true, m_newScene = pnewScene;
    else m_newScene = pnewScene, m_currentScene = pnewScene, pnewScene->setWindow(shared_from_this()); // looks shitty
}


SDL_Renderer* app_window::getRenderer() {
    return m_renderer;
}

vec2f app_window::getSize() {
    int w,h;
    SDL_GetWindowSize(m_sdlWindow, &w, &h);
    return vec2f_make(w,h);
}



scene_ptr app_window::getCurrentScene() {
    return m_currentScene;
}



void app_window::startLoop() {
    std::vector<int> countedTicks;
    int capTimer = 0;
    
    while (isRunning()) {
        capTimer = SDL_GetTicks();
        
        handleEvents();
        if (!RKTWindowBackgrounded) update(), render();
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
        
        
        if (m_currentScene == nullptr && m_newScene != nullptr) {
            m_currentScene = NULL;
            m_showNew = false;
            
            m_newScene->setWindow(this->shared_from_this());
            m_currentScene = m_newScene;
            m_newScene = NULL;
        } else if ((m_showNew && (RKTWindowOverlay.get() == nullptr || (RKTWindowOverlay.get() != nullptr && RKTWindowOverlay->getParent() == nullptr)))) { // TODO: Add Transition between scenes
            RKTWindowOverlay.reset();
            RKTWindowOverlay = sprite::create(texture::create(getSize(), m_nextTransition.color));
            RKTWindowOverlay->setAlpha(0);
            RKTWindowOverlay->setZPosition(__FLT_MAX__);
            m_currentScene->addChild(RKTWindowOverlay);
            
            auto fade = fade_action::create(m_nextTransition.duration, 255);
            fade->setEasingFunction(m_nextTransition.startEasingFunction);
            RKTWindowOverlay->runAction(sequence_action::create({
                fade,
            }), "o");
            
            m_showNew = false;
        } else if (RKTWindowOverlay.get() != nullptr && RKTWindowOverlay->getAction("o") == nullptr && m_newScene != nullptr) {
            
            m_currentScene.reset();
            m_currentScene = m_newScene;
            m_currentScene->setWindow(this->shared_from_this());
            m_newScene.reset();
            
            RKTWindowOverlay->removeFromParent();
            m_currentScene->addChild(RKTWindowOverlay);
            
            auto fade = fade_action::create(m_nextTransition.duration, 0);
            fade->setEasingFunction(m_nextTransition.endEasingFunction);
            RKTWindowOverlay->runAction(sequence_action::create({
                fade,
                remove_action::create(),
            }), "o2");
            
            m_showNew = false;
        }
    }
}


void app_window::handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_running = false;
                RKTLog("Event SDL_QUIT... Bye!");
                break;
            case SDL_KEYDOWN:
                if (m_currentScene != nullptr) m_currentScene->keyDown(KeyCode(event.key.keysym.sym));
                break;
            case SDL_KEYUP:
                if (m_currentScene != nullptr) m_currentScene->keyUp(KeyCode(event.key.keysym.sym));
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (m_currentScene != nullptr) m_currentScene->mouseClickBegan(event.button, getMouseCoords());
                break;
            case SDL_MOUSEMOTION:
                if (m_currentScene != nullptr) m_currentScene->mouseMoved(event.motion, getMouseCoords());
                break;
            case SDL_MOUSEBUTTONUP:
                if (m_currentScene != nullptr) m_currentScene->mouseClickEnded(event.button, getMouseCoords());
                break;
            case SDL_JOYAXISMOTION: { // ACCELEROMETER SUPPORT // TODO: Change EngineHelper's init and this to check for SDL_JoystickDeviceAdded event
                if (event.jaxis.axis == 0) m_accelData.x = event.jaxis.value / CONTROLLER_AXIS_INPUT_RANGE * 5.f;
                if (event.jaxis.axis == 1) m_accelData.y = event.jaxis.value / CONTROLLER_AXIS_INPUT_RANGE * 5.f;
                if (event.jaxis.axis == 2) m_accelData.z = event.jaxis.value / CONTROLLER_AXIS_INPUT_RANGE * 5.f;
                if (m_currentScene != nullptr) m_currentScene->accelerometerMoved(m_accelData);
                break;
            }
            case SDL_FINGERDOWN: {
                if (m_currentScene != nullptr) m_currentScene->touchBegan(event.tfinger, vec2f_make(event.tfinger.x, event.tfinger.y)*getSize());
                break;
            }
            case SDL_FINGERMOTION: {
                if (m_currentScene != nullptr) m_currentScene->touchMoved(event.tfinger, vec2f_make(event.tfinger.x, event.tfinger.y)*getSize());
                break;
            }
            case SDL_FINGERUP: {
                if (m_currentScene != nullptr) m_currentScene->touchEnded(event.tfinger, vec2f_make(event.tfinger.x, event.tfinger.y)*getSize());
                break;
            }
            
            case SDL_CONTROLLERDEVICEADDED:
                RKTLog("CONTROLLER DEVICE ADDED");
                SDL_GameControllerOpen(event.cdevice.which);
                break;
            case SDL_CONTROLLERBUTTONDOWN: {
                if (m_currentScene != nullptr) m_currentScene->controllerPushedButton(event.cdevice.which, (SDL_GameControllerButton)event.cbutton.button);
                break;
            }
            case SDL_CONTROLLERBUTTONUP: {
                if (m_currentScene != nullptr) m_currentScene->controllerReleasedButton(event.cdevice.which, (SDL_GameControllerButton)event.cbutton.button);
                break;
            }
            case SDL_CONTROLLERAXISMOTION: {
                if (m_currentScene != nullptr) m_currentScene->controllerAxisMotion(event.cdevice.which, (SDL_GameControllerAxis)event.caxis.axis, event.caxis.value/CONTROLLER_AXIS_INPUT_RANGE);
                break;
            }
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED && m_currentScene != nullptr) m_currentScene->orientationChange(DeviceOrientationPortrait), RKTLog("app_window data: "<<event.window.data1<<", "<<event.window.data2);
                break;
            }
            
            
            default: break;
        }
    }
}

void app_window::update() {
    if (m_currentScene != nullptr) m_currentScene->update();
}
void app_window::render() {
    if (m_currentScene != nullptr) m_currentScene->render();
}

void app_window::quit() {
    m_running = false;
    
    // TODO: Check
    //SDL_DestroyWindow(m_sdlWindow);
    //SDL_DestroyRenderer(m_renderer);
}

bool app_window::isRunning() {
    return m_running;
}


double app_window::screenScale() {
    if (m_screenScale == -1.f) {
        int x,y;
        SDL_GetWindowSize(m_sdlWindow, &x, &y);
        
        int w,h;
        SDL_GL_GetDrawableSize(m_sdlWindow, &w, &h);
        
        m_screenScale = w/double(x);
    }

    return m_screenScale;
}


RKT_NAMESPACE_END
