

#include "MyScene.hpp"

bool MyScene::init() {
    
    sprite = Sprite::create("activity_indicator.png");
    sprite->setAnchorPoint(Vec2Make(0.5f,0.5f));
    addChild(sprite);
    
    return true;
}

void MyScene::mouseMoved(SDL_MouseMotionEvent, Vec2 coords) {
    
    sprite->setPosition(coords);
    
}