//
//  Node.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Node.hpp"
#include "Scene.hpp"


bool Node::init() {
    children.clear();
    return true;
}

NodePtr Node::create() {
    return NodePtr(new Node());
}
Node::~Node() {
    mParent.reset();
    actions.clear();
    children.clear();
}




void Node::runAction(ActionPtr action) { // WORKS
    std::stringstream stre("");
    stre << rand();
    runAction(std::move(action), stre.str());
}
void Node::runAction(ActionPtr action, const std::string &forKey) { // WORKS
    action->target = this;
    action->start();
    actions[forKey] = (std::move(action));
}

void Node::removeAction(ActionPtr action) { // NOT TESTED
    for(auto iterator = actions.begin(); iterator != actions.end(); iterator++) {
        if (iterator->second == action) {
            return;
        }
    }
}
void Node::removeAction(const std::string &actionName) { // WORKS
    actions[actionName]->finished = true;
}
void Node::removeAllActions() { // NOT TESTED
    for (auto&& a : actions) a.second->finished = true;
}
bool Node::hasActions() {
    return actions.size() > 0;
}
ActionPtr Node::getAction(std::string actionName) {
    return actions.find(actionName) == actions.end() ? NULL : actions[actionName];
}




void Node::update() {
    if (shouldBeRemoved) return;
    for (auto&& i = children.begin(); i != children.end();) {
        auto child = (*i);
        
        if (child->shouldBeRemoved) child->willMoveToParent(NULL), child->shouldBeRemoved = false, i = children.erase(i); // remove finished actions
        else if (i != children.end()) child->update(), ++i;
    }
    for (auto&& i = actions.begin(); i != actions.end();) {
        if (i->second->target == nullptr || i->second->finished) i = actions.erase(i); // remove finished actions
        else i->second->update(), ++i;
    }
}


void Node::willMoveToParent(NodePtr newParent) {
    mParent = newParent;
}


void Node::setPosition(const Vec2 &pos) {
    isTransformDirty = true;
    position = pos;
}
const Vec2 Node::getPosition() {
    return position;
}


void Node::setZRotation(const double &angle) {
    isTransformDirty = true;
    mZRotation = angle;
}
const double Node::getZRotation() {
    return mZRotation;
}


void Node::setAlpha(const int &alpha) {
    mAlpha = alpha;
}
const int Node::getAlpha() {
    return mAlpha;
}


Vec2 Node::getSize() {
    return mSize;
}


void Node::setScale(const double &scale) {
    isTransformDirty = true;
    mScale = scale;
}
const double Node::getScale() {
    return mScale;
}


void Node::setAnchorPoint(Vec2 ap) {
    mAnchorPoint = ap;
}
Vec2 Node::getAnchorPoint() {
    return mAnchorPoint;
}


AffineTransform Node::nodeToWorldTransform() {
    AffineTransform t = nodeToParentTransform();
    for (auto p = NodeWeakPtr(this->getParent()); !p.expired(); p = NodeWeakPtr( p.lock()->getParent() ))
        t = AffineTransformMultiply(t, p.lock()->nodeToParentTransform());
    return t;
}
AffineTransform Node::worldToNodeTransform() {
    return AffineTransformInverse(nodeToWorldTransform());
}
Vec2 Node::convertToNodeSpace(Vec2 worldPoint) {
    Vec2 ret = Vec2ApplyAffineTransform(worldPoint, worldToNodeTransform());
    return ret;
}
Vec2 Node::convertToWorldSpace(Vec2 nodePoint) {
    Vec2 res = Vec2ApplyAffineTransform(nodePoint, nodeToWorldTransform());
    return res;
}





const NodeVector &Node::getChildren() {
    return children;
}
void Node::addChild(const NodePtr& node) {
    node->setParent(shared_from_this());
    node->willMoveToParent(shared_from_this());
    children.push_back(node);
}
void Node::removeFromParent() { // untested
    removeAllActions();
    shouldBeRemoved = true;
}


NodePtr Node::getParent() {
    return mParent.lock();
}
void Node::setParent(const NodePtr& n) {
    mParent.reset();
    mParent = n;
}


ScenePtr Node::getScene() {
    auto p = getParent();
    for (; p->getParent()!=NULL; p = p->getParent());
    return std::static_pointer_cast<Scene>(p);
}


const std::string Node::getName() {
    return name;
}
void Node::setName(std::string n) {
    name = n;
}




void Node::render(SDL_Renderer *renderer) { // render into scene / Surface
    for (auto&& s : children) {
        if (!s->shouldBeRemoved) s->render(renderer);
    }
}





void Node::keyDown(SDL_KeyboardEvent event) {
    for (auto&& c : children) if (c != nullptr) c->keyDown(event);
}
void Node::keyUp(SDL_KeyboardEvent event) {
    for (auto&& c : children) if (c != nullptr) c->keyUp(event);
}
void Node::mouseClickBegan(SDL_MouseButtonEvent event, Vec2 coords) {
    for (auto&& c : children) if (c != nullptr) c->mouseClickBegan(event, coords);
}
void Node::mouseMoved(SDL_MouseMotionEvent event, Vec2 coords) {
    for (auto&& c : children) if (c != nullptr) c->mouseMoved(event, coords);
}
void Node::mouseClickEnded(SDL_MouseButtonEvent event, Vec2 coords) {
    for (auto&& c : children) if (c != nullptr) c->mouseClickEnded(event, coords);
}



void Node::computeTransform() {
    mTransform = AffineTransformIdentity();
    
    auto anchorOffset = getAnchorPoint();
    
    mTransform = AffineTransformMultiply(mTransform, AffineTransformMakeScale(getScale(), getScale()));
    mTransform = AffineTransformMultiply(mTransform, AffineTransformMakeTranslate(anchorOffset.x, anchorOffset.y));
    mTransform = AffineTransformMultiply(mTransform, AffineTransformMakeRotate(getZRotation()));
    mTransform = AffineTransformMultiply(mTransform, AffineTransformMakeTranslate(getPosition().x, getPosition().y));
    
    isTransformDirty = false;
}

AffineTransform Node::nodeToParentTransform() {
    if (isTransformDirty) computeTransform();
    return mTransform;
}
