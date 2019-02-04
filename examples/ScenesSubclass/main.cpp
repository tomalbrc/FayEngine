//
//  main.cpp
//
//  Created by Tom Albrecht on 30.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "FayEngine/FayEngine.h"

#include "MyScene.hpp"


using namespace FE;

int main(int argc, const char * argv[]) {
    auto win = Window::create("Scene example", Vec2Make(400, 400), false);
    
    auto scene = MyScene::create();
    scene->setBackgroundColor(ColorBlackColor());
    
    atan
    
    win->presentScene(scene);
    win->startLoop();
    
    return 0;
}
