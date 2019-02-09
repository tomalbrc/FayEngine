//
//  SpriteAnimationAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 20.12.15.
//  
//

#ifndef SpriteAnimationAction_hpp
#define SpriteAnimationAction_hpp

#include "Action.hpp"
#include "Sprite.hpp"

RKT_NAMESPACE_BEGIN

class SpriteAnimationAction;
RKT_create_shared__ptr(SpriteAnimationAction);

/**
 * Animates a Sequence of Texture objects on the target Sprite
 */
class SpriteAnimationAction : public Action {
public:
    static SpriteAnimationAction_ptr create(double secondsPerFrame, std::vector< Texture_ptr > textures, bool shouldRestoreOriginal);
    static SpriteAnimationAction_ptr create(double secondsPerFrame, std::vector< Texture_ptr > textures);
    ~SpriteAnimationAction();
    
    void update();
    void start();
    
private:
    bool init(double secondsPerFrame, std::vector< Texture_ptr > textures, bool shouldRestoreOriginal);
    Texture_ptr mOriginalTexture;
    bool mShouldRestoreOriginal = true;
    std::vector< Texture_ptr > textures;
};

RKT_NAMESPACE_END
#endif /* SpriteAnimationAction_hpp */
