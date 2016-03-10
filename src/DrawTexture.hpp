//
//  DrawTexture.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 06.03.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef DrawTexture_hpp
#define DrawTexture_hpp

#include <stdio.h>
#include "Texture.hpp"

class DrawTexture;
typedef std::shared_ptr<DrawTexture> DrawTexturePtr;

/**
 * Texture to draw! yea
 */
class DrawTexture /* not sure about the naming convention */ : public Texture  {
    SDL_Surface *m_bufferSurface = NULL;
    bool init(Vec2 size, Color color);
public:
    static DrawTexturePtr create(Vec2 size, Color color);
    ~DrawTexture();
    
    void fillRect(Rect rect, Color color);
    void drawLine(Vec2 p1, Vec2 p2, Color color);
    
    void apply(); // Apply everything
};


template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

#endif /* DrawTexture_hpp */
