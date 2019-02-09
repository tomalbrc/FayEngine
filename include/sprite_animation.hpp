//
//  sprite_animation_action.hpp
//  rawket
//
//  Created by Tom Albrecht on 20.12.15.
//  
//

#ifndef SpriteAnimationAction_hpp
#define SpriteAnimationAction_hpp

#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class sprite_animation_action;
RKT_create_shared__ptr(sprite_animation_action);

/**
 * Animates a Sequence of texture objects on the target sprite
 */
class sprite_animation_action : public action {
public:
    static sprite_animation_action_ptr create(double secondsPerFrame, std::vector< texture_ptr > textures, bool shouldRestoreOriginal);
    static sprite_animation_action_ptr create(double secondsPerFrame, std::vector< texture_ptr > textures);
    ~sprite_animation_action();
    
    void update();
    void start();
    
private:
    bool init(double secondsPerFrame, std::vector< texture_ptr > textures, bool shouldRestoreOriginal);
    texture_ptr mOriginalTexture;
    bool mShouldRestoreOriginal = true;
    std::vector< texture_ptr > textures;
};

RKT_NAMESPACE_END
#endif /* SpriteAnimationAction_hpp */
