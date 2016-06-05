//
//  DrawTexture.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 06.03.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef DrawTexture_hpp
#define DrawTexture_hpp

#include "Texture.hpp"
#include "Types.hpp"

FE_NAMESPACE_BEGIN

class DrawTexture;
FE_create_Ptr(DrawTexture);

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
    void fillCircle(float radius, Vec2 origin, Color color);
    
    void apply(); // Apply everything
};


template <typename T> int sign(T val) { // TODO: Do something with this, this is not the right place for this func.
    return (T(0) < val) - (val < T(0));
}

FE_NAMESPACE_END
#endif /* DrawTexture_hpp */
