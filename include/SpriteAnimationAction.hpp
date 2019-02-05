//
//  SpriteAnimationAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 20.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef SpriteAnimationAction_hpp
#define SpriteAnimationAction_hpp

#include "Action.hpp"
#include "Sprite.hpp"

FE_NAMESPACE_BEGIN

class SpriteAnimationAction;
FE_create_shared_Ptr(SpriteAnimationAction);

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

FE_NAMESPACE_END
#endif /* SpriteAnimationAction_hpp */
