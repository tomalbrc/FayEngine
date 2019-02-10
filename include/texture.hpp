//
//  texture.hpp
//  rawket
//
//  Created by Tom Albrecht on 12.12.15.
//  
//

#ifndef Texture_hpp
#define Texture_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "node.hpp"

RKT_NAMESPACE_BEGIN

class texture;
rkt_create_ptr(texture);

/**
 * This class allows to easily create SDL textures from image files or create new blank textures with a specified size and color
 */
class texture {
public:
    /**
     * Creates a new texture object with a width and height of 0 and an RGBA of {0,0,0,255}
     *
     * @return  shared pointer to a new texture instance
     */
    static texture_ptr create();
    
    /**
     * Creates a new texture object from an image file. The file may be an PNG, JPEG or any other format SDL2_image supports
     *
     * @param   filename    Filename to an image file
     * @return 	shared pointer to a new texture instance
     */
    static texture_ptr create(std::string filename);
    
    /**
     * Creates a new texture object (rectangle) with Size and color4u
     *
     * @param	size            Size for the new texture
     * @param	color           color4u for the new texture
     * @return 	shared pointer to a new texture instance
     */
    static texture_ptr create(vec2f size, color4u color);
    
    /**
     * Creates a new texture object from another texture with a rectangle and stores a reference to the source texture
     *
     * @param	sourceTexture   Source texture
     * @param	rectangle            rectangle to 'cut' the new texture out
     * @return 	shared pointer to a new texture instance
     */
    static texture_ptr create(texture_ptr sourceTexture, rectangle rectangle);
    
    /**
     * Creates a new texture object from an SDL_Surface
     *
     * @param	surface         Pointer to a valid SDL_Surface
     * @return 	shared pointer to a new texture instance
     */
    static texture_ptr create(SDL_Surface *surface);
    
    /**
     * Deletes the original SDL_Texture if the texture wasn't created using texture::create(texture_ptr tex, rectangle rectangle)
     */
    ~texture();
    
    /**
     * Returns the dimensions of the texture
     *
     * @return a vec2f containing the current size of the texture
     */
    vec2f getSize();
    
    /**
     * Returns the render offset from a batched texture.
     * If the texture isn't batched the render-offset will return vec2f_null()
     *
     * @return a vec2f containing the offset of the texture if created from a source texture
     */
    vec2f getRenderOffset();
    
    /**
     * A pointer to the original SDL_texture. 
     * Every texture created through a create() function is guranteed to have this pointer set.
     *
     * @return a pointer to the original SDL_texture
     */
    SDL_Texture* sdlTexture();
    
private:
    texture_ptr mSourceTexture = NULL;
    texture_ptr mBatchTexture;
    vec2f mRenderOffset = vec2f_null();
    
    bool init();
    bool init(std::string filename); // load image from path
    bool init(vec2f size, color4u col);
    bool init(texture_ptr source, rectangle rectangle);
    bool init(texture_ptr tex); // Passes ownership to engine_helper
    bool init(SDL_Surface *surface);
    
protected:
    SDL_Texture *mTexture = NULL;
    vec2f mSize = vec2f_null();
};
    
RKT_NAMESPACE_END
#endif /* Texture_hpp */
