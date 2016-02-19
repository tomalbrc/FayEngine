//
//  SpriteAnimationAction.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 20.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef SpriteAnimationAction_hpp
#define SpriteAnimationAction_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#include "Action.hpp"
#include "Sprite.hpp"

class SpriteAnimationAction;
typedef std::unique_ptr<SpriteAnimationAction> SpriteAnimationActionPtr;
class Node;

/**
 * Animates a Sequence of Texture objects on the target Sprite
 */
class SpriteAnimationAction : public Action {
public:
    static SpriteAnimationActionPtr create(double secondsPerFrame, std::vector< TexturePtr > textures, bool shouldRestoreOriginal);
    static SpriteAnimationActionPtr create(double secondsPerFrame, std::vector< TexturePtr > textures);
    ~SpriteAnimationAction();
    
    void update();
    void start();
    
private:
    bool init(double secondsPerFrame, std::vector< TexturePtr > textures, bool shouldRestoreOriginal);
    TexturePtr mOriginalTexture;
    bool mShouldRestoreOriginal = true;
    std::vector< TexturePtr > textures;
};

#endif /* SpriteAnimationAction_hpp */
