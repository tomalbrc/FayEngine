//
//  Texture.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Node.hpp"

class Texture;
FE_create_Ptr(Texture);

/**
 * This class allows to easily create SDL textures from image files or create new blank textures with a specified size and color
 */
class Texture {
public:
    /**
     * Creates a new Texture object with a width and height of 0 and an RGBA of {0,0,0,255}
     *
     * @return  shared pointer to a new Texture instance
     */
    static TexturePtr create();
    
    /**
     * Creates a new Texture object from an image file. The file may be an PNG, JPEG or any other format SDL2_image supports
     *
     * @param   filename    Filename to an image file
     * @return 	shared pointer to a new Texture instance
     */
    static TexturePtr create(std::string filename);
    
    /**
     * Creates a new Texture object (rectangle) with Size and Color
     *
     * @param	size            Size for the new Texture
     * @param	color           Color for the new Texture
     * @return 	shared pointer to a new Texture instance
     */
    static TexturePtr create(Vec2 size, Color color);
    
    /**
     * Creates a new Texture object from another Texture with a rect and stores a reference to the source Texture
     *
     * @param	sourceTexture   Source Texture
     * @param	rect            Rect to 'cut' the new Texture out
     * @return 	shared pointer to a new Texture instance
     */
    static TexturePtr create(TexturePtr sourceTexture, Rect rect);
    
    /**
     * Creates a new Texture object from an SDL_Surface
     *
     * @param	surface         Pointer to a valid SDL_Surface
     * @return 	shared pointer to a new Texture instance
     */
    static TexturePtr create(SDL_Surface *surface);
    
    /**
     * Deletes the original SDL_Texture if the Texture wasn't created using Texture::create(TexturePtr tex, Rect rect)
     */
    ~Texture();
    
    /**
     * Returns the dimensions of the Texture
     *
     * @return a Vec2 containing the current size of the Texture
     */
    Vec2 getSize();
    
    /**
     * Returns the render offset from a batched texture.
     * If the Texture isn't batched the render-offset will return Vec2Null()
     *
     * @return a Vec2 containing the offset of the Texture if created from a source Texture
     */
    Vec2 getRenderOffset();
    
    /**
     * A pointer to the original SDL_texture. 
     * Every Texture created through a create() function is guranteed to have this pointer set.
     *
     * @return a pointer to the original SDL_texture
     */
    SDL_Texture* sdlTexture();
    
private:
    TexturePtr mSourceTexture = NULL;
    TexturePtr mBatchTexture;
    Vec2 mRenderOffset = Vec2Null();
    
    bool init();
    bool init(std::string filename); // load image from path
    bool init(Vec2 size, Color col);
    bool init(TexturePtr source, Rect rect);
    bool init(TexturePtr tex); // Passes ownership to EngineHelper
    bool init(SDL_Surface *surface);
    
protected:
    SDL_Texture *mTexture = NULL;
    Vec2 mSize = Vec2Null();
};
#endif /* Texture_hpp */
