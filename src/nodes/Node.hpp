//
//  Node.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>

//#ifdef __linux__
#include <algorithm>
#include <functional>
//#endif

#include "Action.hpp"

#define Logbuch(x)  std::cout << "[LOGBUCHEINTRAG:] " << x << std::endl
//#define Logbuch(x) 0

struct Color {
    Uint32 r,g,b,a;
};
extern Color ColorMake(Uint32 r, Uint32 g, Uint32 b, Uint32 a);
extern Color ColorMake(Uint32 r, Uint32 g, Uint32 b);
inline Color ColorBlackColor() { return ColorMake(0, 0, 0); }
inline Color ColorWhiteColor() { return ColorMake(255, 255, 255); }
inline Color ColorRedColor() { return ColorMake(255, 0, 0); }
inline Color ColorBlueColor() { return ColorMake(0, 0, 255); }
inline Color ColorGreenColor() { return ColorMake(0, 255, 0); }
inline Color ColorCyanColor() { return ColorMake(0, 255, 255); } //
inline Color ColorMagentaColor() { return ColorMake(255, 0, 255); }
inline Color ColorYellowColor() { return ColorMake(255, 255, 0); }
inline Color ColorPurpleColor() { return ColorMake(128, 0, 128); }
inline Color ColorOrangeColor() { return ColorMake(255, 165, 0); }
inline Color ColorGrayColor() { return ColorMake(128, 128, 128); }
inline Color ColorLightGrayColor() { return ColorMake(211, 211, 211); }
inline Color ColorDarkGrayColor() { return ColorMake(169, 169, 169); }



struct Vec2 {
    float x,y;
};

extern Vec2 Vec2Make(float x, float y);
extern Vec2 Vec2Null();


extern bool operator==(Vec2 lhs, const Vec2& rhs);
extern Vec2 operator+(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator-(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator-(const Vec2 rhs);
extern Vec2 operator/(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator/(Vec2 lhs, const int rhs);
extern Vec2 operator*(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator*(Vec2 lhs, const float rhs);



struct Rect {
    Vec2 origin, size;
};

extern Rect RectMake(float x, float y, float w, float h);
extern Rect RectMake(Vec2 origin, Vec2 size);
extern Rect RectNull();

extern bool RectIntersectsVec2(Rect r, Vec2 v);
extern bool RectIntersectsRect(Rect rectA, Rect rectB);




class Scene;
class Node;
typedef std::shared_ptr<Node> NodePtr;
typedef std::weak_ptr<Node> NodeWeakPtr;
typedef std::vector<NodePtr> NodeVector;
typedef std::map<std::string, ActionPtr> ActionMap;
// redefinition :(
typedef std::shared_ptr<Scene> ScenePtr;
typedef std::weak_ptr<Scene> SceneWeakPtr;

class Node : public std::enable_shared_from_this<Node> {
public:
    static NodePtr create();
    virtual ~Node();
    
    // Alle methoden um Aktionen hunzuzufügen oder zu entfernen
    // (mithilfe eines keys)
    void runAction(ActionPtr action);
    void runAction(ActionPtr action, const std::string& forKey);
    void removeAction(ActionPtr action);
    void removeAction(const std::string& actionName);
    void removeAllActions();
    
    // update methode (für runActions)
    virtual void update();
    
    // Node Lifecycle
    virtual void willMoveToParent(NodePtr oldParent);
    virtual void willRemoveFromParent(NodePtr oldParent);
    
    
    void setName(std::string n);
    const std::string getName();
    
    void setPosition(const Vec2 &pos);
    const Vec2 getPosition();
    
    void setZRotation(const int &angle);
    const int getZRotation();
    
    void setAlpha(const int &a);
    const int getAlpha();
    
    void setScale(const double &scale);
    const double getScale();
    
    void addChild(const NodePtr& node);
    const NodeVector &getChildren();
    void removeFromParent();
    
    NodePtr getParent();
    void setParent(const NodePtr& n);
    ScenePtr getScene();
    
    // eine virtuelle function nullsetzen heißt das jede
    // derivierte klasse diese funktion implementieren !muss!
    virtual void keyDown(SDL_KeyboardEvent event);
    virtual void keyUp(SDL_KeyboardEvent event);
    virtual void mouseMoved(SDL_MouseMotionEvent, Vec2 coords);
    virtual void mouseClickEnded(SDL_MouseButtonEvent event, Vec2 coords);
    virtual void mouseClickBegan(SDL_MouseButtonEvent event, Vec2 coords);
    
    const Vec2 convertToWorldSpace(const Vec2 &v); // Works reliable
    const Vec2 convertToNodeSpace(const Vec2 &v); // Needs testing
    
    virtual void render(SDL_Renderer *renderer);
    
    
protected:
    bool init();
    // flag ob die Node beim nächsten rendern entfernt werden soll
    bool shouldBeRemoved = false;
private:
    // Alpha wert
    int mAlpha = 255;
    
    // Rotation auf der z Achse in Grad
    int mZRotation = 0;
    
    // Skalierung (Skaliert Größe)
    double mScale = 1.0;
    
    // Position in parent node
    Vec2 position = Vec2Make(0,0);
    
    // Children of this node, vector< Node* >
    NodeVector children;  // children.clear() is in init
    
    // name of the node (TODO: Add getChildNodeNamed(std::string name))
    std::string name = "";
    
    // parent of this noded
    NodeWeakPtr mParent;
    
    // actions, performed in public
    ActionMap actions;
    
    // fast selbsterklärend, die absolute position in der scene
    Vec2 nodeToWindowPosition();

};

#endif /* Node_hpp */
