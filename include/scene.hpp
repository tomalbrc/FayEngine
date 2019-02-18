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
#include "types.hpp"
#include "node.hpp"
#include "app_window.hpp"

RKT_NAMESPACE_BEGIN

class scene;
rkt_create_ptr(scene);

/**
 * scene Class
 */
class scene : public node {
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
     * Sets the background color4u for the scene
     *
	 * @param backgroundColor new background color4u
     */
    void setBackgroundColor(color4u backgroundColor);
    
    /**
     * The current background color4u for the scene
     *
     * @return current background color4u
     */
    color4u getBackgroundColor();
    
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
     * Re-implement the render function from node
	 *
	 * TODO: Documentation is lacking
     */
    virtual void render(SDL_Renderer *renderer = nullptr) override;
    
    /**
     * Set if the cursor should be shown or not
     *
     * @param show	flag to set wether to show or hide the cursor
	 *
	 * TODO: Documentation is lacking
     */
    virtual void setShowCursor(bool show);
	
    /**
     * Re-implementation of node::update()
     */
    virtual void update() override;
	
    /**
     * Mobile device related. Gets called when the device orientation is changed.
     * Check types.hpp for supported 'DeviceOrientation's
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
    color4u mBackgroundColor;
    app_window_ptr window;
};

RKT_NAMESPACE_END
#endif /* Scene_hpp */
