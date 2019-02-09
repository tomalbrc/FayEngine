//
//  node.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.12.15.
//  
//

#include "node.hpp"
#include "scene.hpp"
#include "engine_helper.hpp"

RKT_NAMESPACE_BEGIN

bool node::init() {
    children.clear();
    return true;
}

node_ptr node::create() {
    return node_ptr(new node());
}
node::~node() {
    mParent.reset();
    actions.clear();
    children.clear();
}




void node::runAction(action_ptr action) { // WORKS
    std::stringstream stre;
    stre << rand();
    runAction(std::move(action), stre.str());
}
void node::runAction(action_ptr action, const std::string &forKey) { // WORKS
    action->target = this;
    action->start();
    actions[forKey] = std::move(action);
}

void node::removeAction(action_ptr action) { // NOT TESTED
    action->finished = true;
}

void node::removeAction(const std::string &actionName) { // WORKS
    if (actions[actionName] != nullptr) {
        actions[actionName]->finished = true;
    }
}

void node::removeAllActions() { // NOT TESTED
    for (auto& a : actions) if (a.second != nullptr) a.second->finished = true;
}

bool node::hasActions() {
    return actions.size() > 0;
}

const action_ptr node::getAction(const std::string& actionName) {
    decltype(auto) action = actions[actionName];
    if (action && !action->finished) {
        return actions[actionName];
    }
    else return nullptr;
}



inline void sort(std::vector<node_ptr>& children) {
    std::sort(children.begin( ), children.end( ), [ ]( const node_ptr& lhs, const node_ptr& rhs ) {
        return (lhs == nullptr ? 0 : lhs->getZPosition()) < (rhs == nullptr ? 0 : rhs->getZPosition());
    });
}
void node::update() {
    for (auto&& i = actions.begin(); i != actions.end();) {
        if (i->second == nullptr || i->second->finished) i = actions.erase(i); // remove finished actions
        else i->second->update(), ++i;
    }
    for (auto&& i = children.begin(); i != children.end();) {
        decltype(auto) child = *i;
        if (child == nullptr) i = children.erase(i); // remove finished actions
        else if (i != children.end()) child->update(), ++i;
    }
    
    if (hasDirtyZPos) sort(children), hasDirtyZPos = false;
}


void node::willMoveToParent(node_ptr newParent) {
    mParent = newParent;
}


void node::setPosition(const vec2f &pos) {
    isTransformDirty = true;
    position = pos;
}
const vec2f node::getPosition() {
    return position;
}


void node::setZRotation(const double &angle) {
    isTransformDirty = true;
    mZRotation = angle;
}
const double node::getZRotation() {
    return mZRotation;
}


void node::setAlpha(const int &alpha) {
    mAlpha = alpha;
}
const int node::getAlpha() {
    return mAlpha;
}


void node::setScale(vec2f scale) {
    isTransformDirty = true;
    mScale = scale;
}
const vec2f node::getScale() {
    return mScale;
}


void node::setAnchorPoint(vec2f ap) {
    mAnchorPoint = ap;
}
const vec2f node::getAnchorPoint() {
    return mAnchorPoint;
}


affine_transform node::nodeToWorldTransform() {
    affine_transform t = nodeToParentTransform();
    for (auto p = getParent(); p != nullptr; p = p->getParent())
        t = transform_multiply(t, p->nodeToParentTransform());
    return t;
}
affine_transform node::worldToNodeTransform() {
    return transform_inv(nodeToWorldTransform());
}
vec2f node::convertToNodeSpace(vec2f worldPoint) {
    vec2f ret = vec2f_apply_transform(worldPoint, worldToNodeTransform());
    return ret;
}
vec2f node::convertToWorldSpace(vec2f nodePoint) {
    vec2f res = vec2f_apply_transform(nodePoint, nodeToWorldTransform());
    return res;
}





const node_vector &node::getChildren() {
    return children;
}
void node::addChild(const node_ptr& node) {
    hasDirtyZPos = true;
    node->setParent(shared_from_this());
    node->willMoveToParent(shared_from_this());
    children.push_back(node);
}
void node::removeFromParent() { // untested
    removeAllActions();
    if (getParent() != nullptr) getParent()->removeChild(this->shared_from_this()), mParent.reset();
}

void node::removeChild(node_ptr node) {
    node->willMoveToParent(nullptr);
    for (auto&& c : children) {
        if (node.get() == c.get()) {
            c.reset();
            break;
        }
    }
}


const node_ptr node::getParent() const {
    return mParent;
}
void node::setParent(const node_ptr& n) {
    if (mParent != nullptr) mParent.reset();
    mParent = n;
}


const scene_ptr node::getScene() {
    // Ugh, not sure about this
    return engine_helper::getInstance()->getMainWindow()->getCurrentScene();
}


const int node::getTag() {
    return mTag;
}

void node::setTag(int tag) {
    mTag = tag;
}


const std::string node::getName() {
    return name;
}
void node::setName(std::string n) {
    name = n;
}




void node::render(SDL_Renderer *renderer) { // render into scene / Surface
    for (auto& s : children) {
        if (s) s->render(renderer);
    }
}





void node::keyDown(KeyCode key) {
    for (auto&& c : children) if (c != nullptr) c->keyDown(key);
}
void node::keyUp(KeyCode key) {
    for (auto&& c : children) if (c != nullptr) c->keyUp(key);
}
void node::mouseClickBegan(SDL_MouseButtonEvent event, vec2f coords) {
    for (auto&& c : children) if (c != nullptr) c->mouseClickBegan(event, coords);
}
void node::mouseMoved(SDL_MouseMotionEvent event, vec2f coords) {
    for (auto&& c : children) if (c != nullptr) c->mouseMoved(event, coords);
}
void node::mouseClickEnded(SDL_MouseButtonEvent event, vec2f coords) {
    for (auto&& c : children) if (c != nullptr) c->mouseClickEnded(event, coords);
}


void node::touchBegan(SDL_TouchFingerEvent finger, vec2f coords) {
    for (auto&& c : children) if (c != nullptr) c->touchBegan(finger, coords);
}
void node::touchMoved(SDL_TouchFingerEvent finger, vec2f coords) {
    for (auto&& c : children) if (c != nullptr) c->touchMoved(finger, coords);
}
void node::touchEnded(SDL_TouchFingerEvent finger, vec2f coords) {
    for (auto&& c : children) if (c != nullptr) c->touchEnded(finger, coords);
}
void node::accelerometerMoved(vec3f accelerometerData) {
    for (auto&& c : children) if (c != nullptr) c->accelerometerMoved(accelerometerData);
}

void node::controllerPushedButton(Sint32 controllerIndex, SDL_GameControllerButton button) {
    for (auto&& c : children) if (c != nullptr) c->controllerPushedButton(controllerIndex, button);
}
void node::controllerReleasedButton(Sint32 controllerIndex, SDL_GameControllerButton button) {
    for (auto&& c : children) if (c != nullptr) c->controllerReleasedButton(controllerIndex, button);
}
void node::controllerAxisMotion(Sint32 controllerIndex, SDL_GameControllerAxis axis, float value) {
    for (auto&& c : children) if (c != nullptr) c->controllerAxisMotion(controllerIndex, axis, value);
}




void node::computeTransform() {
    mTransform = affine_transform_id();
    
    decltype(auto) anchorOffset = getAnchorPoint();
    
    mTransform = transform_multiply(mTransform, transform_make_scale(getScale().x, getScale().y));
    mTransform = transform_multiply(mTransform, transform_make_translate(anchorOffset.x, anchorOffset.y));
    mTransform = transform_multiply(mTransform, transform_make_rot(getZRotation()));
    mTransform = transform_multiply(mTransform, transform_make_translate(getPosition().x, getPosition().y));
    
    isTransformDirty = false;
}

affine_transform node::nodeToParentTransform() {
    if (isTransformDirty) computeTransform();
    return mTransform;
}




void node::setZPosition(float zpos) {
    if (getParent() && m_zPosition != zpos) getParent()->hasDirtyZPos = true;
    m_zPosition = zpos;
}

const float node::getZPosition() {
    return m_zPosition;
}

RKT_NAMESPACE_END
