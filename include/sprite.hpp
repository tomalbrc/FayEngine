//
// sprite.hpp
// Tom Albrecht, 06.12.15 - 01:13
//

#ifndef SPRITE
#define SPRITE 1


#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "node.hpp"
#include "texture.hpp"
#include "engine_helper.hpp"

RKT_NAMESPACE_BEGIN

class sprite;
RKT_create_ptr(sprite);

/**
 * sprite Class inherits from node Class
 */
class sprite : public node {
public:
    /**
     * Creates an new sprite object without a texture
     *
     * @return s shared_ptr to the new sprite instance
     */
    static sprite_ptr create();
    
    /**
     * Creates an new sprite object with a texture
     *
     * @return s shared_ptr to the new sprite instance
     */
    static sprite_ptr create(texture_ptr t);
    
    /**
     * Creates an new sprite object with desired dimensions for a new texture
     *
     * @return s shared_ptr to the new sprite instance
     */
    static sprite_ptr create(vec2f dimensions);
    
    /**
     * Creates an new sprite with a texture loaded from an image file
     *
     * @return s shared_ptr to the new sprite instance
     */
    static sprite_ptr create(std::string filename);
    
    /**
     * Deconstructor
     */
    ~sprite();
    
    /**
     *  @return the current size of the texture
     */
    virtual vec2f getSize();
    
    /**
     * Gives the sprite a new texture 
     *
     * @param new texture
     */
    virtual void setTexture(texture_ptr tex);
    
    /**
     * @return the current texture of the sprite
     */
    virtual texture_ptr getTexture();
    
    /**
     * The current blend mode of the sprite
     *
     * @return the current blend mode of the sprite
     */
    virtual BlendMode getBlendMode();
    
    /**
     * Sets the blend mode for the sprite.
     * See types.hpp for details
     *
     * @param new blend mode
     */
    virtual void setBlendMode(BlendMode mode);
    
    /**
     * Rectangle relative to parent's coordinate space
     *
     * @return a rectangle containg the origin and size
     */
    rectangle getRect();
    
    /**
     * Rectangle in local coordinate space
     *
     * @return a rectangle containg the origin and size
     */
    rectangle getBoundingBox();
    
    /**
     * Re-implementation of node::render(SDL_Renderer)
     */
    virtual void render(SDL_Renderer *renderer);
    
    /**
     * Sets the color to use for color mod using Formula (via SDL):
     * srcC = srcC * (color / 255)
     *
     * @param   color4u   Alpha Channel is ignored
     */
    virtual void setColor(color4u color);
    
    /**
     * Returns the current color used for color mod
     */
    virtual color4u getColor();
    
private:
    color4u m_color = color_make(255u, 255u, 255u, 255u);
    vec2f mSize = vec2f_null();
    texture_ptr mTexture = NULL;
    BlendMode m_blendMode = BlendModeAlpha;
protected:
    bool init();
    bool init(texture_ptr texture);
    bool init(vec2f dimensions); // empty sprite
    bool init(std::string filename); // load sprite with texture from filename
};


RKT_NAMESPACE_END
#endif
