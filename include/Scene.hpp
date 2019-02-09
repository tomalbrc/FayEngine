//
//  Scene.hpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//  
//

#ifndef Scene_hpp
#define Scene_hpp

#include "SDL.h"
#include "Types.hpp"
#include "Node.hpp"
#include "Window.hpp"

FE_NAMESPACE_BEGIN

class Scene;
FE_create_Ptr(Scene);

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
    virtual WindowPtr getWindow();
    
    /**
     * Re-implement the render function from Node
     */
    virtual void render();
    
    /**
     * Set if the cursor should be shown or not
     *
     * @param flag to set wether to show or hide the cursor
     */
    virtual void setShowCursor(bool show);
    
    
    /**
     * Re-implementation of Node::update()
     */
    virtual void update();
    
    
    /**
     * Mobile device related. Gets called when the device orientation is changed.
     * Check Types.hpp for supported 'DeviceOrientation's
     */
    virtual void orientationChange(DeviceOrientation newOrientation);
    
    
    /**
     * iOS, Android and WinRT related
     */
    virtual void applicationWillEnterForeground();
    
    /**
     * iOS, Android and WinRT related
     */
    virtual void applicationDidEnterForeground();
    
    /**
     * iOS, Android and WinRT related
     */
    virtual void applicationWillEnterBackground();
    
    /**
     * iOS, Android and WinRT related
     */
    virtual void applicationDidEnterBackground();
    
protected:
    Scene();
    bool init();
    bool shouldBeRemoved = false;
private:
    Color mBackgroundColor;
    WindowPtr window;
};

FE_NAMESPACE_END
#endif /* Scene_hpp */
