//
//  Node.hpp
//  PixelDead_SDL
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


class Scene;
class Node;
FE_create_Ptr(Scene);
FE_create_Ptr(Node);
typedef std::vector<NodePtr> NodeVector;
typedef std::map<std::string, ActionPtr> ActionMap;
// redefinition :(

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
    void runAction(ActionPtr action);
    
    /**
     * Run an Action for a specified key
     *
     * @param action    action to run
     * @param forKey    key to run the Action for
     */
    void runAction(ActionPtr action, const std::string& forKey);
    
    /**
     * Removes a running action
     *
     * @param action    action to remove
     */
    void removeAction(ActionPtr action);
    
    /**
     * Removes a running action for a specified key
     *
     * @param actionName    key of the action to remove
     */
    void removeAction(const std::string& actionName);
    
    /**
     * Removes all running actions
     */
    void removeAllActions();
    
    /**
     * Get an action by key
     *
     * @param actionName    key of the action
     */
    ActionPtr getAction(std::string actionName);
    
    
    bool hasActions();
    
    // update methode (für runActions)
    virtual void update();
    
    // Node Lifecycle
    virtual void willMoveToParent(NodePtr oldParent);
    
    void setName(std::string n);
    const std::string getName();
    
    void setPosition(const Vec2 &pos);
    const Vec2 getPosition();
    
    void setZRotation(const double &angle);
    const double getZRotation();
    
    void setAlpha(const int &a);
    const int getAlpha();
    
    void setScale(Vec2 scale);
    const Vec2 getScale();
    
    // void setSize(Vec2 size) doesnt exist (yet)
    Vec2 getSize();
    
    void setAnchorPoint(Vec2 ap);
    Vec2 getAnchorPoint();
    
    void addChild(const NodePtr& node);
    const NodeVector &getChildren();
    void removeFromParent();
    void removeChild(NodePtr node);
    
    NodePtr getParent();
    void setParent(const NodePtr& n);
    ScenePtr getScene();
    
    int getTag();
    void setTag(int tag);
    
    // Desktop functions
    virtual void keyDown(FEKeyCode key);
    virtual void keyUp(FEKeyCode key);
    virtual void mouseMoved(SDL_MouseMotionEvent, Vec2 coords);
    virtual void mouseClickEnded(SDL_MouseButtonEvent event, Vec2 coords);
    virtual void mouseClickBegan(SDL_MouseButtonEvent event, Vec2 coords);
    
    // Mobile functions
    virtual void touchBegan(SDL_TouchFingerEvent finger, Vec2 coords);
    virtual void touchEnded(SDL_TouchFingerEvent finger, Vec2 coords);
    virtual void touchMoved(SDL_TouchFingerEvent finger, Vec2 coords);
    virtual void accelerometerMoved(Vec3 accelerometerData);
    
    virtual void controllerPushedButton(Sint32 controllerIndex, SDL_GameControllerButton button);
    virtual void controllerReleasedButton(Sint32 controllerIndex, SDL_GameControllerButton button);
    virtual void controllerAxisMotion(Sint32 controllerIndex, SDL_GameControllerAxis axis, Sint16 value);
    
    
    
    Vec2 convertToWorldSpace(Vec2 v); // Works reliable
    Vec2 convertToNodeSpace(Vec2 v); // Needs testing
    
    AffineTransform worldToNodeTransform();
    AffineTransform nodeToWorldTransform();
    
    virtual void render(SDL_Renderer *renderer);
    
protected:
    bool init();
private:
    int mTag = 0;
    
    // Alpha
    int mAlpha = 255;
    
    // Rotation on the z axis in degree
    double mZRotation = 0.0;
    
    // Scale
    Vec2 mScale = Vec2Make(1.0, 1.0);
    
    // Position in parent node
    Vec2 position = Vec2Make(0,0);
    
    // Children of this node, vector< Node* >
    NodeVector children;  // children.clear() is in init
    
    // name of the node (TODO: Add getChildNodeNamed(std::string name))
    std::string name = "";
    
    // parent of this noded
    NodeWeakPtr mParent;
    
    // size, content-size
    Vec2 mSize = Vec2Null();
    
    // actions, performed in public
    ActionMap actions;
    
    bool isTransformDirty = true;
    AffineTransform mTransform;
    void computeTransform();
    AffineTransform nodeToParentTransform();
    
    Vec2 mAnchorPoint = Vec2Null();
    
};

#endif /* Node_hpp */
