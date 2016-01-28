//
//  MyScene.cpp
//

#include "MyScene.hpp"

// little c helper func
std::string particleString(int i) {
    std::string s = "";
    if (i < 10) s = "0"; // 01...14
    return "particlefx_" + s + std::to_string(i) + ".png";
}

bool MyScene::init() {
    
    return true;
}

void MyScene::setWindow(Window *window) {
    Scene::setWindow(window);
    
    sprite = Sprite::create("particlefx_01.png");
    sprite->setScale(1.0);
    sprite->setAnchorPoint(Vec2Make(0.5,0.5));
    sprite->setPosition(getWindow()->getSize()/2.0);
    this->addChild(sprite);
    
    infoLabel = LabelNode::create("txt", "Pacifico.ttf", 26);
    this->addChild(infoLabel);
    
    animateForImageIndex();
}



void MyScene::keyDown(SDL_KeyboardEvent event) {
    if (event.keysym.sym == SDLK_LEFT) {
        if (index > 1) --index;
        animateForImageIndex();
    }
    if (event.keysym.sym == SDLK_RIGHT) {
        if (index < 14) ++index;
        animateForImageIndex();
    }
    
    if (event.keysym.sym == SDLK_f) {
        animationSpeed -= 0.1;
        animateForImageIndex();
    }
    if (event.keysym.sym == SDLK_s) {
        animationSpeed += 0.1;
        animateForImageIndex();
    }
    
    
    if (event.keysym.sym == SDLK_PLUS) {
        sprite->setScale(sprite->getScale()+0.1);
    }
    if (event.keysym.sym == SDLK_MINUS) {
        sprite->setScale(sprite->getScale()-0.1);
    }
    
    if (event.keysym.sym == SDLK_SPACE) {
        setPaused(!isPaused());
    }
    
    if (event.keysym.sym == SDLK_q) {
        getWindow()->quit();
    }
}


void MyScene::update() {
    Scene::update();
    
    infoLabel->setText("Spritesheet: \"" + particleString(index) + "\"  |  Scale: "+std::to_string(sprite->getScale())+"x  |   Duration: "+std::to_string(animationSpeed)+"s");
}


void MyScene::animateForImageIndex() {
    std::vector<TexturePtr> textures; // 2-Dimensionale array (a vector containing vectors containing Textures)
    
    auto tiles = 8.0;
    auto imageSize = Vec2Make(1024,1024);
    
    auto sourceTex = Texture::create(particleString(index)); // 8x8 sprites
    auto imageDimensions = Vec2Make(imageSize.x/tiles,imageSize.y/tiles);
    
    for (int y = 0; y < tiles; y++) {
        for (int x = 0; x < tiles; x++) {
            textures.push_back(Texture::create(sourceTex, RectMake(x*imageDimensions.x,y*imageDimensions.y,imageDimensions.x,imageDimensions.y)));
        }
    }
    
    sprite->removeAllActions();
    sprite->setTexture(textures[0]);
    sprite->runAction(RepeatAction::create(
                                           SpriteAnimationAction::create(animationSpeed, textures), 0 // 0 = repeat forever
                                           ));
    

}