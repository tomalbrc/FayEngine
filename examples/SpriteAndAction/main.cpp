//
//  main.cpp
//
//  Created by Tom Albrecht on 30.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "FayEngine/FayEngine.h"

int main(int argc, const char * argv[]) {

    auto win = Window::create("Sprite & Action example", Vec2Make(400, 400), false);
    auto scene = Scene::create();
    scene->setBackgroundColor(ColorBlackColor());
    
    auto s = Sprite::create("activity_indicator.png");
    s->setAnchorPoint(Vec2Make(0.5, 0.5));
    s->setPosition(win->getSize()/2.0);
    s->runAction(RotateToAction::create(20, 360*20));
    scene->addChild(s);
    
    win->presentScene(scene);
    win->startLoop();
    
    return 0;
}
