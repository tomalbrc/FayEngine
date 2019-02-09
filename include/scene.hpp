//
//  scene.hpp
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
#include "app_window.hpp"

RKT_NAMESPACE_BEGIN

class scene;
RKT_create__ptr(scene);

/**
 * scene Class
 */
class scene : public Node {
public:
    /**
     * Creates a new scene object
     *
     * @return a shared_ptr to the new scene instance
     */
    static scene_ptr create();
    
    /**
     * Deconstructor
     */
    virtual ~scene();
    
    /**
     * Sets the background Color for the scene
     *
     * @param new background Color
     */
    void setBackgroundColor(Color backgroundColor);
    
    /**
     * The current background Color for the scene
     *
     * @return current background Color
     */
    Color getBackgroundColor();
    
    /**
     * Sets a new window. Normally called when presenting a new scene
     *
     * @param window new app_window
     */
    virtual void setWindow(app_window_ptr window);
    
    /**
     * The current window the scene is presented in
     *
     * @return current window
     */
    virtual app_window_ptr getWindow();
    
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
    scene();
    bool init();
    bool shouldBeRemoved = false;
private:
    Color mBackgroundColor;
    app_window_ptr window;
};

RKT_NAMESPACE_END
#endif /* Scene_hpp */
