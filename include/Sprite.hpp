//
// Sprite.hpp
// Tom Albrecht, 06.12.15 - 01:13
// (Copyright)
//

#ifndef SPRITE
#define SPRITE 1


#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Node.hpp"
#include "Texture.hpp"
#include "EngineHelper.hpp"

FE_NAMESPACE_BEGIN

class Sprite;
FE_create_Ptr(Sprite);

/**
 * Sprite Class inherits from Node Class
 */
class Sprite : public Node {
public:
    /**
     * Creates an new Sprite object without a Texture
     *
     * @return s shared_ptr to the new Sprite instance
     */
    static SpritePtr create();
    
    /**
     * Creates an new Sprite object with a Texture
     *
     * @return s shared_ptr to the new Sprite instance
     */
    static SpritePtr create(TexturePtr t);
    
    /**
     * Creates an new Sprite object with desired dimensions for a new Texture
     *
     * @return s shared_ptr to the new Sprite instance
     */
    static SpritePtr create(Vec2 dimensions);
    
    /**
     * Creates an new Sprite with a Texture loaded from an image file
     *
     * @return s shared_ptr to the new Sprite instance
     */
    static SpritePtr create(std::string filename);
    
    /**
     * Deconstructor
     */
    ~Sprite();
    
    /**
     *  @return the current size of the Texture
     */
    virtual Vec2 getSize();
    
    /**
     * Gives the Sprite a new Texture 
     *
     * @param new Texture
     */
    virtual void setTexture(TexturePtr tex);
    
    /**
     * @return the current Texture of the Sprite
     */
    virtual TexturePtr getTexture();
    
    /**
     * The current blend mode of the Sprite
     *
     * @return the current blend mode of the sprite
     */
    virtual BlendMode getBlendMode();
    
    /**
     * Sets the blend mode for the Sprite.
     * See Types.hpp for details
     *
     * @param new blend mode
     */
    virtual void setBlendMode(BlendMode mode);
    
    /**
     * Rectangle relative to parent's coordinate space
     *
     * @return a Rect containg the origin and size
     */
    Rect getRect();
    
    /**
     * Rectangle in local coordinate space
     *
     * @return a Rect containg the origin and size
     */
    Rect getBoundingBox();
    
    /**
     * Re-implementation of Node::render(SDL_Renderer)
     */
    virtual void render(SDL_Renderer *renderer);
    
    /**
     * Sets the color to use for color mod using Formula (via SDL):
     * srcC = srcC * (color / 255)
     *
     * @param   Color   Alpha Channel is ignored
     */
    virtual void setColor(Color color);
    
    /**
     * Returns the current color used for color mod
     */
    virtual Color getColor();
    
private:
    Color m_color = ColorMake(255, 255, 255, 255);
    Vec2 mSize = Vec2Null();
    TexturePtr mTexture = NULL;
    BlendMode m_blendMode = BlendModeAlpha;
protected:
    bool init();
    bool init(TexturePtr texture);
    bool init(Vec2 dimensions); // empty sprite
    bool init(std::string filename); // load sprite with texture from filename
};


FE_NAMESPACE_END
#endif