//
//  Node.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Node.hpp"
#include "Scene.hpp"


extern Color ColorMake(Uint32 r, Uint32 g, Uint32 b, Uint32 a) {
    Color c;
    c.r = r, c.g = g, c.b = b, c.a = a;
    return c;
}
extern Color ColorMake(Uint32 r, Uint32 g, Uint32 b) { return ColorMake(r, g, b, 255); }



extern Vec2 Vec2Make(float x, float y) {
    Vec2 p;
    p.x = x;
    p.y = y;
    return p;
}
extern Vec2 Vec2Null() {
    Vec2 p;
    p.x = 0.f;
    p.y = 0.f;
    return p;
}
extern bool operator==(Vec2 lhs, const Vec2& rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y); }
extern Vec2 operator+(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x + rhs.x, lhs.y + rhs.y); }
extern Vec2 operator-(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x - rhs.x, lhs.y - rhs.y); }
extern Vec2 operator-(const Vec2 rhs) { return Vec2Make(-rhs.x, -rhs.y); }
extern Vec2 operator/(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x / rhs.x, lhs.y / rhs.y); }
extern Vec2 operator/(Vec2 lhs, const int rhs) { return Vec2Make(lhs.x / rhs, lhs.y / rhs); }
extern Vec2 operator*(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x * rhs.x, lhs.y * rhs.y); }
extern Vec2 operator*(Vec2 lhs, const float rhs) { return Vec2Make((lhs.x * rhs), (lhs.y * rhs)); }



extern Rect RectMake(Vec2 origin, Vec2 size) {
    return RectMake(origin.x, origin.y, size.x, size.y);
}
extern Rect RectMake(float x, float y, float w, float h) {
    Rect p;
    p.origin.x = x;
    p.origin.y = y;
    p.size.x = w;
    p.size.y = h;
    return p;
}
extern bool RectIsNull(Rect p) {
    return (bool)(p.origin.x == 0 && p.origin.y == 0 && p.size.x == 0 && p.size.y == 0);
}
extern bool RectIntersectsVec2(Rect r, Vec2 v) {
    double pointX = v.x;
    double pointY = v.y;
    if (pointX < (r.origin.x + r.size.x) && pointX > r.origin.x &&
        pointY < (r.origin.y + r.size.y) && pointY > r.origin.y)
        return true;
    else
        return false;
}
extern bool RectIntersectsRect(Rect rectA, Rect rectB) {
    return !((rectA.origin.x + rectA.size.x) < rectB.origin.x ||
             rectB.origin.x + rectB.size.x < rectA.origin.x ||
             (rectA.origin.y+rectA.size.y) < rectB.origin.y ||
             (rectB.origin.y+rectB.size.y) < rectA.origin.y);
}









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
    actions[actionName] = std::move(actions[actionName]);
}
void Node::removeAllActions() { // NOT TESTED
    for (auto&& a : actions) a.second->finished = true;
}


void Node::update() {
    for (auto&& i = children.begin(); i != children.end();) {
        if ((*i)->shouldBeRemoved) (*i)->willMoveToParent(NULL), i = children.erase(i); // remove finished actions
        else if (i != children.end()) {
            (*i)->update(), ++i;
        }
    }
    for (auto&& i = actions.begin(); i != actions.end();) {
        if (i->second->target == nullptr || i->second->finished) i = actions.erase(i); // remove finished actions
        else i->second->update(), ++i;
    }
}


void Node::willMoveToParent(NodePtr oldParent) {}
void Node::willRemoveFromParent(NodePtr oldParent) {}



void Node::setPosition(const Vec2 &pos) {
    position = pos;
}
const Vec2 Node::getPosition() {
    return position;
}


const int Node::getZRotation() {
    return mZRotation;
}
void Node::setZRotation(const int &angle) {
    mZRotation = angle;
}


void Node::setAlpha(const int &alpha) {
    mAlpha = alpha;
}
const int Node::getAlpha() {
    return mAlpha;
}


void Node::setScale(const double &scale) {
    mScale = scale;
}
const double Node::getScale() {
    return mScale;
}


Vec2 Node::nodeToWindowPosition() {
    Vec2 t = getPosition();
    for (auto p = NodeWeakPtr(this->getParent()); !p.expired(); p = NodeWeakPtr( p.lock()->getParent() ))
        t = (t + p.lock()->getPosition());
    return t;
}
const Vec2 Node::convertToNodeSpace(const Vec2 &worldPoint) {
    Vec2 t = this->getParent()->convertToWorldSpace(this->getPosition());
    Vec2 ret = worldPoint-t;
    return ret;
}
const Vec2 Node::convertToWorldSpace(const Vec2 &nodePoint) {
    Vec2 ret = nodePoint + nodeToWindowPosition();
    return ret;
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
            s->render(renderer);
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




