//
//  main.cpp
//

#include "FayEngine/FayEngine.h"

#include "MyScene.hpp"

using namespace FE;

int main(int argc, const char * argv[]) {
    EngineHelper::getInstance()->Init();
    
    auto scene = MyScene::create();
    scene->setBackgroundColor(ColorBlackColor());
    
    auto win = Window::create("Subtextures and Animation", EngineHelper::getInstance()->getDiplaySize(), false);
    win->presentScene(scene);
    win->startLoop();
    
    return 0;
}
