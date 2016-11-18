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
    /**
     * Creates a new texture filled with a given color
     *
     * @param size	The size of the texture in pixels
     * @param color	Color used to fill the newly created texture
     */
    static DrawTexturePtr create(Vec2 size, Color color);

    /**
     * Destructor
     */
    ~DrawTexture();
    
    /**
     * Fills a rectangle on the texture "buffer" with a given color
     *
     * @param rect	Rectangle
     * @param color	The color of the rectangle
     */
    void fillRect(Rect rect, Color color);

    /**
     * Draws a 1 pixel thick line from point 1 to point 2 using a specified color
     *
     * @param p1	Starting point to draw the line from
     * @param p2	Ending point to draw the line to
     * @param color	Color of the line
     */
    void drawLine(Vec2 p1, Vec2 p2, Color color);

    /**
     * Fills a circle using a radius and color, centered at the origin
     *
     * @param radius	Radius for the circle
     * @param origin	Origin of the circle on the texture (centered)
     * @param color	Color used to fill the circle
     */
    void fillCircle(float radius, Vec2 origin, Color color);
    
    /**
     * Uploads the "buffer" texture to the GPU (effectively creating an SDL_Texture)
     */
    void apply(); // Apply everything
};


template <typename T> int sign(T val) { // TODO: Do something with this, this is not the right place for this function. lol
    return (T(0) < val) - (val < T(0));
}

FE_NAMESPACE_END
#endif /* DrawTexture_hpp */
