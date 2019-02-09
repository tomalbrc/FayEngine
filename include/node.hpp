//
//  node.hpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#ifndef Node_hpp
#define Node_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>

#include <algorithm>
#include <functional>
#include <memory>

#include "types.hpp"
#include "action.hpp"

RKT_NAMESPACE_BEGIN

class scene;
class node;
RKT_create_ptr(scene);
RKT_create_ptr(node);
typedef std::vector<node_ptr> NodeVector;
typedef std::map<std::string, action_ptr> ActionMap;
// redefvirtual inition :(

/**
 * node Class
 */
class node : public std::enable_shared_from_this<node> {
public:
    /**
     * Creates a new node object
     *
     * @return a shared_ptr to the new node instance
     */
    static node_ptr create();
    
    /**
     * Deconstructor
     */
    virtual ~node();
    
    /**
     * Run an action
     *
     * @param action    action to run
     */
    virtual void runAction(action_ptr action);
    
    /**
     * Run an action for a specified key
     *
     * @param action    action to run
     * @param forKey    key to run the action for
     */
    virtual void runAction(action_ptr action, const std::string& forKey);
    
    /**
     * Removes a running action
     *
     * @param action    action to remove
     */
    virtual void removeAction(action_ptr action);
    
    /**
     * Removes a running action for a specified key
     *
     * @param actionName    key of the action to remove
     */
    virtual void removeAction(const std::string& actionName);
    
    /**
     * Removes all running actions
     */
    virtual void removeAllActions();
    
    /**
     * Get an action by key
     *
     * @param actionName    key of the action
     */
    virtual const action_ptr getAction(std::string actionName);
    
    /**
     * Returns true if the node has any active actions
     */
    virtual bool hasActions();
    
    /**
     * Update method. Called every frame.
     */
    virtual void update();
    
    /**
     * Gets called when the node is about to move to a new parent.
     *
     * @param newParent     the parent the node will be moved to
     */
    virtual void willMoveToParent(node_ptr newParent);
    
    /**
     * Sets the name of the node
     *
     * @param name  new name for the node
     */
    virtual void setName(std::string name);
    
    /**
     * Returns the current name of the node
     */
    virtual const std::string getName();
    
    /**
     * Gives the node a new position relative to it's parents coordinate system
     *
     * @param pos   new position
     */
    virtual void setPosition(const vec2f &pos);
    
    /**
     * Returns the current position relative to the parent coordinate system
     */
    virtual const vec2f getPosition();
    
    /**
     * Sets a new rotation on the z-axis. In Radians
     *
     * @param angle     angle in radians
     */
    virtual void setZRotation(const double &angle);
    
    /**
     * Returns the current rotation on the z-axis of the node. In radians
     */
    virtual const double getZRotation();
    
    /**
     * Sets a new alpha, ranges from 0 to 255
     *
     * @param a new alpha value
     */
    virtual void setAlpha(const int &a);
    
    /**
     * Returns the current alpha value. Ranges between 0 and 255
     */
    virtual const int getAlpha();
    
    /**
     * Sets a new scale for the node. Default is {1.0, 1.0}
     *
     * @param scale     new scale
     */
    virtual void setScale(vec2f scale);
    
    /**
     * Returns the current scale of the node as a vec2f
     */
    virtual const vec2f getScale();
    
    /**
     * Sets a new anchor point. Default is {0,0}
     *
     * {0,0}--{1,0}
     *   |      |
     *   |      |
     * {0,1}--{1,1}
     *
     * @param ap    new anchor point
     */
    virtual void setAnchorPoint(vec2f ap);
    
    /**
     * Returns the current anchor point. See setAnchorPoint(vec2f) for a short explanation.
     * Defaults to {0,0}
     */
    virtual const vec2f getAnchorPoint();
    
    /**
     * Adds a new child to the node; willMoveToParent and setParent will be called on the passed node
     *
     * @param node to add
     */
    virtual void addChild(const node_ptr& node);
    
    /**
     * Returns all children in an std::vector<node_ptr>
     */
    virtual const NodeVector &getChildren();
    
    /**
     * Removes the node from it's parent
     */
    virtual void removeFromParent();
    
    /**
     * Removes a child node from the node
     *
     * @param node  node to remove
     */
    virtual void removeChild(node_ptr node);
    
    /**
     * Returns the parent of the node, NULL if the node doesn't have a parent
     */
    virtual const node_ptr getParent();
    
    /**
     *
     * Sets the new parent of the node
     */
    virtual void setParent(const node_ptr& n);
    
    /**
     * Returns the current scene the node is in. Returns NULL when none of the nodes in the graph is on the scene
     */
    virtual const scene_ptr getScene();
    
    /**
     * Returns the tag of the node. int
     */
    virtual const int getTag();
    
    /**
     * Sets a new tag for the node.
     *
     * @param tag   new tag
     */
    void setTag(int tag);
    
    /**
     * Keyboard key down
     *
     * @param key   the key that will be pressed
     */
    virtual void keyDown(KeyCode key);
    
    /**
     * Keyboard key up
     *
     * @param key   the key that will be pressed
     */
    virtual void keyUp(KeyCode key);
    
    /**
     * Mouse pointer moved
     *
     * @param event     SDL mouse event
     * @param coords    coords in window
     */
    virtual void mouseMoved(SDL_MouseMotionEvent event, vec2f coords);
    
    /**
     * Mouse button click ended
     *
     * @param event     SDL mouse event
     * @param coords    coords in window
     */
    virtual void mouseClickEnded(SDL_MouseButtonEvent event, vec2f coords);
    
    /**
     * Mouse button click began
     *
     * @param event     SDL mouse event
     * @param coords    coords in window
     */
    virtual void mouseClickBegan(SDL_MouseButtonEvent event, vec2f coords);
    
    /**
     * Touch Began input for mobile devices
     *
     * @param event     SDL finger event
     * @param coords    coords in window
     */
    virtual void touchBegan(SDL_TouchFingerEvent finger, vec2f coords);
    
    /**
     * Touch Ended input for mobile devices
     *
     * @param event     SDL finger event
     * @param coords    coords in window
     */
    virtual void touchEnded(SDL_TouchFingerEvent finger, vec2f coords);
    
    /**
     * Touch Moved input for mobile devices
     *
     * @param event     SDL finger event
     * @param coords    coords in window
     */
    virtual void touchMoved(SDL_TouchFingerEvent finger, vec2f coords);
    
    /**
     * Accelerometer data for mobile devices
     *
     * @param accelerometerData a vec3f containing x,y and z data from the accelerometer. Ranges between -1.0 and 1.0
     */
    virtual void accelerometerMoved(vec3f accelerometerData);
    
    // TODO: tvOS controller support!
    /**
     * Controller pushed button
     *
     * @param controllerIndex   index of the controller that pushed the button
     * @param button            button that was being pressed
     */
    virtual void controllerPushedButton(Sint32 controllerIndex, SDL_GameControllerButton button);
    
    /**
     * Controller released a button
     *
     * @param controllerIndex   index of the controller that pushed the button
     * @param button            button that was being released
     */
    virtual void controllerReleasedButton(Sint32 controllerIndex, SDL_GameControllerButton button);
    
    /**
     * Controller axis value changed / has motion
     *
     * @param controllerIndex   index of the controller that changed an axis value
     * @param axis              axis that was moved
     * @param value             Ranges between -1.0 and 1.0
     */
    virtual void controllerAxisMotion(Sint32 controllerIndex, SDL_GameControllerAxis axis, float value);
    
    /**
     * Converts a position from node-space to world-space.
     *
     * @param position  position in node-space
     */
    vec2f convertToWorldSpace(vec2f position);
    
    /**
     * Convert a position from world-space to node-space
     */
    vec2f convertToNodeSpace(vec2f position);
    
    /**
     * Transformation of the world to the node
     */
    affine_transform worldToNodeTransform();
    
    /**
     * Transformation of the node to the world
     */
    affine_transform nodeToWorldTransform();
    
    /**
     * Renders the content. Walks through scene graph
     */
    virtual void render(SDL_Renderer *renderer);
    
    /**
     * Sets the z-position in parent node
     *
     * @param zpos  new z-Position
     */
    virtual void setZPosition(float zpos);
    
    /**
     * Returns the current z-position in parent node
     */
    virtual const float getZPosition();
    
protected:
    bool init();
private:
    int mTag = 0;
    
    // Alpha
    int mAlpha = 255;
    
    // Rotation on the z axis in degree
    double mZRotation = DegreesToRadians(0.0);
    
    // Scale
    vec2f mScale = vec2f_make(1.0, 1.0);
    
    // Position in parent node
    vec2f position = vec2f_make(0,0);
    
    // Children of this node, vector< node* >
    NodeVector children;  // children.clear() is in init
    
    // name of the node (TODO: Add getChildNodeNamed(std::string name))
    std::string name = "";
    
    // parent of this noded
    node_ptr mParent;
    
    
    // actions, performed in public
    ActionMap actions;
    
    bool isTransformDirty = true;
    affine_transform mTransform;
    void computeTransform();
    affine_transform nodeToParentTransform();
    
    vec2f mAnchorPoint = vec2f_null();
    
    bool hasDirtyZPos = true;
    
    float m_zPosition = 0.f;
};

RKT_NAMESPACE_END
#endif /* Node_hpp */
