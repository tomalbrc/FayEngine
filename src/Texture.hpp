//
//  Texture.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 12.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Node.hpp"

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

class Texture {
public:
    /**
     * Creates an empty texture with a width and height of 0 and an RGBA of (0,0,0,255)
     *
     * @return  shared pointer to a new Texture instance
     */
    static TexturePtr create();
    
    /**
     * Creates a texture from an image file. The file may be an PNG, JPEG or any other format SDL_image supports
     *
     * @param   filename    Filename to an image file
     * @return 	shared pointer to a new Texture instance
     */
    static TexturePtr create(std::string filename);
    
    /**
     * Creates a texture (rectangle) with size and color
     *
     * @param	size            Size for the new Texture
     * @param	color           Color for the new Texture
     * @return 	shared pointer to a new Texture instance
     */
    static TexturePtr create(Vec2 size, Color color);
    
    /**
     * Creates a texture from another texture with a rect and stores a reference to the source texture
     *
     * @param	sourceTexture   Source texture
     * @param	rect            Rect to 'cut' the new texture out
     * @return 	shared pointer to a new Texture instance
     */
    static TexturePtr create(TexturePtr tex, Rect rect);
    
    /**
     * Creates a texture from an SDL_Surface
     *
     * @param	surface         Pointer to a valid SDL_Surface
     * @return 	shared pointer to a new Texture instance
     */
    static TexturePtr create(SDL_Surface *surface);
    
    /**
     * Destructor
     */
    ~Texture();
    
    
    Vec2 getSize();
    Vec2 getRenderOffset();
    
    SDL_Texture* sdlTexture();
    
    
    
    
    
    
private:
    TexturePtr mSourceTexture = NULL;
    SDL_Texture *mTexture = NULL;
    std::shared_ptr<Texture> mBatchTexture;
    Vec2 mRenderOffset = Vec2Null();
    Vec2 mSize = Vec2Null();
    
    bool init();
    bool init(std::string filename); // load image from path
    bool init(Vec2 size, Color col);
    bool init(TexturePtr source, Rect rect);
    bool init(TexturePtr tex); // Passes ownership to EngineHelper
    bool init(SDL_Surface *surface);
};
#endif /* Texture_hpp */
