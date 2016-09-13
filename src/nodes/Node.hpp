//
//  Node.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
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

#include "Types.hpp"
#include "Action.hpp"

FE_NAMESPACE_BEGIN

class Scene;
class Node;
FE_create_Ptr(Scene);
FE_create_Ptr(Node);
typedef std::vector<NodePtr> NodeVector;
typedef std::map<std::string, ActionPtr> ActionMap;
// redefvirtual inition :(

/**
 * Node Class
 */
class Node : public std::enable_shared_from_this<Node> {
public:
    /**
     * Creates a new Node object
     *
     * @return a shared_ptr to the new Node instance
     */
    static NodePtr create();
    
    /**
     * Deconstructor
     */
    virtual ~Node();
    
    /**
     * Run an action
     *
     * @param action    action to run
     */
    virtual void runAction(ActionPtr action);
    
    /**
     * Run an Action for a specified key
     *
     * @param action    action to run
     * @param forKey    key to run the Action for
     */
    virtual void runAction(ActionPtr action, const std::string& forKey);
    
    /**
     * Removes a running action
     *
     * @param action    action to remove
     */
    virtual void removeAction(ActionPtr action);
    
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
    virtual const ActionPtr getAction(std::string actionName);
    
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
    virtual void willMoveToParent(NodePtr newParent);
    
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
    virtual void setPosition(const Vec2 &pos);
    
    /**
     * Returns the current position relative to the parent coordinate system
     */
    virtual const Vec2 getPosition();
    
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
    virtual void setScale(Vec2 scale);
    
    /**
     * Returns the current scale of the node as a Vec2
     */
    virtual const Vec2 getScale();
    
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
    virtual void setAnchorPoint(Vec2 ap);
    
    /**
     * Returns the current anchor point. See setAnchorPoint(Vec2) for a short explanation.
     * Defaults to {0,0}
     */
    virtual const Vec2 getAnchorPoint();
    
    /**
     * Adds a new child to the node; willMoveToParent and setParent will be called on the passed node
     *
     * @param Node to add
     */
    virtual void addChild(const NodePtr& node);
    
    /**
     * Returns all children in an std::vector<NodePtr>
     */
    virtual const NodeVector &getChildren();
    
    /**
     * Removes the node from it's parent
     */
    virtual void removeFromParent();
    
    /**
     * Removes a child node from the node
     *
     * @param node  Node to remove
     */
    virtual void removeChild(NodePtr node);
    
    /**
     * Returns the parent of the node, NULL if the node doesn't have a parent
     */
    virtual const NodePtr getParent();
    
    /**
     *
     * Sets the new parent of the node
     */
    virtual void setParent(const NodePtr& n);
    
    /**
     * Returns the current Scene the node is in. Returns NULL when none of the nodes in the graph is on the Scene
     */
    virtual const ScenePtr getScene();
    
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
    virtual void keyDown(FEKeyCode key);
    
    /**
     * Keyboard key up
     *
     * @param key   the key that will be pressed
     */
    virtual void keyUp(FEKeyCode key);
    
    /**
     * Mouse pointer moved
     *
     * @param event     SDL mouse event
     * @param coords    coords in window
     */
    virtual void mouseMoved(SDL_MouseMotionEvent event, Vec2 coords);
    
    /**
     * Mouse button click ended
     *
     * @param event     SDL mouse event
     * @param coords    coords in window
     */
    virtual void mouseClickEnded(SDL_MouseButtonEvent event, Vec2 coords);
    
    /**
     * Mouse button click began
     *
     * @param event     SDL mouse event
     * @param coords    coords in window
     */
    virtual void mouseClickBegan(SDL_MouseButtonEvent event, Vec2 coords);
    
    /**
     * Touch Began input for mobile devices
     *
     * @param event     SDL finger event
     * @param coords    coords in window
     */
    virtual void touchBegan(SDL_TouchFingerEvent finger, Vec2 coords);
    
    /**
     * Touch Ended input for mobile devices
     *
     * @param event     SDL finger event
     * @param coords    coords in window
     */
    virtual void touchEnded(SDL_TouchFingerEvent finger, Vec2 coords);
    
    /**
     * Touch Moved input for mobile devices
     *
     * @param event     SDL finger event
     * @param coords    coords in window
     */
    virtual void touchMoved(SDL_TouchFingerEvent finger, Vec2 coords);
    
    /**
     * Accelerometer data for mobile devices
     *
     * @param accelerometerData a Vec3 containing x,y and z data from the accelerometer. Ranges between -1.0 and 1.0
     */
    virtual void accelerometerMoved(Vec3 accelerometerData);
    
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
    Vec2 convertToWorldSpace(Vec2 position);
    
    /**
     * Convert a position from world-space to node-space
     */
    Vec2 convertToNodeSpace(Vec2 position);
    
    /**
     * Transformation of the world to the node
     */
    AffineTransform worldToNodeTransform();
    
    /**
     * Transformation of the node to the world
     */
    AffineTransform nodeToWorldTransform();
    
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
    Vec2 mScale = Vec2Make(1.0, 1.0);
    
    // Position in parent node
    Vec2 position = Vec2Make(0,0);
    
    // Children of this node, vector< Node* >
    NodeVector children;  // children.clear() is in init
    
    // name of the node (TODO: Add getChildNodeNamed(std::string name))
    std::string name = "";
    
    // parent of this noded
    NodePtr mParent;
    
    
    // actions, performed in public
    ActionMap actions;
    
    bool isTransformDirty = true;
    AffineTransform mTransform;
    void computeTransform();
    AffineTransform nodeToParentTransform();
    
    Vec2 mAnchorPoint = Vec2Null();
    
    bool hasDirtyZPos = true;
    
    float m_zPosition = 0.f;
};

FE_NAMESPACE_END
#endif /* Node_hpp */
