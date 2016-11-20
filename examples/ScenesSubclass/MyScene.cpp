

#include "MyScene.hpp"

using namespace FE;

bool MyScene::init() {
    setShowCursor(false);

    sprite = Sprite::create("crosshair_cursor.png");
    sprite->setScale(Vec2Make(0.25f));
    sprite->setAnchorPoint(Vec2Make(0.5f,0.5f));
    addChild(sprite);
    
    return true;
}

void MyScene::mouseMoved(SDL_MouseMotionEvent, Vec2 coords) {
    
    sprite->setPosition(coords);
    
}
