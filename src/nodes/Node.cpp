//
//  Node.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#include "Node.hpp"
#include "Scene.hpp"
#include "EngineHelper.hpp"

FE_NAMESPACE_BEGIN

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
    action->finished = true;
}

void Node::removeAction(const std::string &actionName) { // WORKS
    if (actions[actionName] != nullptr) {
        actions[actionName]->finished = true;
    }
}

void Node::removeAllActions() { // NOT TESTED
    for (auto&& a : actions) if (a.second != nullptr) a.second->finished = true;
}

bool Node::hasActions() {
    return actions.size() > 0;
}

const ActionPtr Node::getAction(std::string actionName) {
   if (actions[actionName] != nullptr && !actions[actionName]->finished) {
        //FELog(actions[actionName]);
        return actions[actionName];
    }
    else return nullptr;
}



inline void sort(std::vector<NodePtr>& children) {
    std::sort(children.begin( ), children.end( ), [ ]( const NodePtr& lhs, const NodePtr& rhs ) {
        return (lhs == nullptr ? 0 : lhs->getZPosition()) < (rhs == nullptr ? 0 : rhs->getZPosition());
    });
}
void Node::update() {
    for (auto&& i = actions.begin(); i != actions.end();) {
        if (i->second == nullptr || i->second->finished) i = actions.erase(i); // remove finished actions
        else i->second->update(), ++i;
    }
    for (auto&& i = children.begin(); i != children.end();) {
        auto child = *i;
        if (child == nullptr) i = children.erase(i); // remove finished actions
        else if (i != children.end()) child->update(), ++i;
    }
    
    // this feels Inefficient :(
    if (hasDirtyZPos) sort(children), hasDirtyZPos = false;
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


void Node::setScale(Vec2 scale) {
    isTransformDirty = true;
    mScale = scale;
}
const Vec2 Node::getScale() {
    return mScale;
}


void Node::setAnchorPoint(Vec2 ap) {
    mAnchorPoint = ap;
}
const Vec2 Node::getAnchorPoint() {
    return mAnchorPoint;
}


AffineTransform Node::nodeToWorldTransform() {
    AffineTransform t = nodeToParentTransform();
    for (auto p = getParent(); p != nullptr; p = p->getParent())
        t = AffineTransformMultiply(t, p->nodeToParentTransform());
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
    hasDirtyZPos = true;
    node->setParent(shared_from_this());
    node->willMoveToParent(shared_from_this());
    children.push_back(node);
}
void Node::removeFromParent() { // untested
    removeAllActions();
    if (getParent() != nullptr) getParent()->removeChild(this->shared_from_this()), mParent.reset();
}

void Node::removeChild(NodePtr node) {
    node->willMoveToParent(NULL);
    for (auto&& c : children) {
        if (node.get() == c.get()) {
            c.reset();
            break;
        }
    }
}


const NodePtr Node::getParent() {
    return mParent;
}
void Node::setParent(const NodePtr& n) {
    if (mParent != nullptr) mParent.reset();
    mParent = n;
}


const ScenePtr Node::getScene() {
    // Ugh, not sure about this
    return EngineHelper::getInstance()->getMainWindow()->getCurrentScene();
}


const int Node::getTag() {
    return mTag;
}

void Node::setTag(int tag) {
    mTag = tag;
}


const std::string Node::getName() {
    return name;
}
void Node::setName(std::string n) {
    name = n;
}




void Node::render(SDL_Renderer *renderer) { // render into scene / Surface
    auto childrenClone = children;
    
    for (auto&& s : children) {
        if (s != nullptr) s->render(renderer);
    }
}





void Node::keyDown(KeyCode key) {
    for (auto&& c : children) if (c != nullptr) c->keyDown(key);
}
void Node::keyUp(KeyCode key) {
    for (auto&& c : children) if (c != nullptr) c->keyUp(key);
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


void Node::touchBegan(SDL_TouchFingerEvent finger, Vec2 coords) {
    for (auto&& c : children) if (c != nullptr) c->touchBegan(finger, coords);
}
void Node::touchMoved(SDL_TouchFingerEvent finger, Vec2 coords) {
    for (auto&& c : children) if (c != nullptr) c->touchMoved(finger, coords);
}
void Node::touchEnded(SDL_TouchFingerEvent finger, Vec2 coords) {
    for (auto&& c : children) if (c != nullptr) c->touchEnded(finger, coords);
}
void Node::accelerometerMoved(Vec3 accelerometerData) {
    for (auto&& c : children) if (c != nullptr) c->accelerometerMoved(accelerometerData);
}

void Node::controllerPushedButton(Sint32 controllerIndex, SDL_GameControllerButton button) {
    for (auto&& c : children) if (c != nullptr) c->controllerPushedButton(controllerIndex, button);
}
void Node::controllerReleasedButton(Sint32 controllerIndex, SDL_GameControllerButton button) {
    for (auto&& c : children) if (c != nullptr) c->controllerReleasedButton(controllerIndex, button);
}
void Node::controllerAxisMotion(Sint32 controllerIndex, SDL_GameControllerAxis axis, float value) {
    for (auto&& c : children) if (c != nullptr) c->controllerAxisMotion(controllerIndex, axis, value);
}




void Node::computeTransform() {
    mTransform = AffineTransformIdentity();
    
    auto anchorOffset = getAnchorPoint();
    
    mTransform = AffineTransformMultiply(mTransform, AffineTransformMakeScale(getScale().x, getScale().y));
    mTransform = AffineTransformMultiply(mTransform, AffineTransformMakeTranslate(anchorOffset.x, anchorOffset.y));
    mTransform = AffineTransformMultiply(mTransform, AffineTransformMakeRotate(getZRotation()));
    mTransform = AffineTransformMultiply(mTransform, AffineTransformMakeTranslate(getPosition().x, getPosition().y));
    
    isTransformDirty = false;
}

AffineTransform Node::nodeToParentTransform() {
    if (isTransformDirty) computeTransform();
    return mTransform;
}





void Node::setZPosition(float zpos) {
    if (getParent() != nullptr && m_zPosition != zpos) getParent()->hasDirtyZPos = true;
    m_zPosition = zpos;
}

const float Node::getZPosition() {
    return m_zPosition;
}


FE_NAMESPACE_END
