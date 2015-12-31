//
//  main.cpp
//
//  Created by Tom Albrecht on 30.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "FayEngine/FayEngine.h"

int main(int argc, const char * argv[]) {
    EngineHelper::getInstance()->setEnableVSync(true);
    
    auto win = Window::create("Multiple Texture & Animation example", Vec2Make(400, 400), false);
    auto scene = Scene::create();
    scene->setBackgroundColor(ColorBlackColor());
    
    std::vector<TexturePtr> textures;
    auto texture = Texture::create("spriteSheet.png");
    auto tSize = texture->getSize();
    int numSprites = 8;
    for (int i = 0; i < numSprites; i++) {
        auto r = RectMake(i*(tSize.x/numSprites),0,(tSize.x/numSprites),325);
        auto t = Texture::create(texture, r);
        textures.push_back(t);
    }
    
    auto s = Sprite::create();
    s->setAnchorPoint(Vec2Make(0.5, 0.5));
    s->setPosition(win->getSize()/2.0);
    s->runAction(SpriteAnimationAction::create(0.5, textures));
    scene->addChild(s);
    
    win->presentScene(scene);
    win->startLoop();
    
    return 0;
}
