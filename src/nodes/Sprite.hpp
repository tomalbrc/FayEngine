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
    Vec2 getSize();
    
    /**
     * Gives the Sprite a new Texture 
     *
     * @param new Texture
     */
    void setTexture(TexturePtr tex);
    
    /**
     * @return the current Texture of the Sprite
     */
    TexturePtr getTexture();
    
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
    
private:
    Vec2 mSize = Vec2Null();
    TexturePtr mTexture = NULL;
protected:
    bool init();
    bool init(TexturePtr texture);
    bool init(Vec2 dimensions); // empty sprite
    bool init(std::string filename); // load sprite with texture from filename
};



#endif