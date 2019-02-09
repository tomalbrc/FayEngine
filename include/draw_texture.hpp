//
//  draw_texture.hpp
//  rawket
//
//  Created by Tom Albrecht on 06.03.16.
//  
//

#ifndef DrawTexture_hpp
#define DrawTexture_hpp

#include "texture.hpp"
#include "types.hpp"

RKT_NAMESPACE_BEGIN

class draw_texture;
RKT_create_ptr(draw_texture);

/**
 * texture to draw! yea
 */
class draw_texture /* not sure about the naming convention */ : public texture  {
    SDL_Surface *m_bufferSurface = NULL;
    bool init(vec2f size, color4u color);
public:
    /**
     * Creates a new texture filled with a given color
     *
     * @param size	The size of the texture in pixels
     * @param color	color4u used to fill the newly created texture
     */
    static draw_texture_ptr create(vec2f size, color4u color);

    /**
     * Destructor
     */
    ~draw_texture();
    
    /**
     * Fills a rectangle on the texture "buffer" with a given color
     *
     * @param rectangle	Rectangle
     * @param color	The color of the rectangle
     */
    void fillRect(rectangle rectangle, color4u color);

    /**
     * Fills an ellipse within a given rectangle with a color
     *
     * @param rectangle	Rectangle to use
     * @param	col	color4u to use
     */
    void fillEllipse(rectangle rectangle, color4u col);

    /**
     * Draws a 1 pixel thick line from point 1 to point 2 using a specified color
     *
     * @param p1	Starting point to draw the line from
     * @param p2	Ending point to draw the line to
     * @param color	color4u of the line
     */
    void drawLine(vec2f p1, vec2f p2, color4u color);

    /**
     * Fills a circle using a radius and color, centered at the origin
     *
     * @param radius	Radius for the circle
     * @param origin	Origin of the circle on the texture (centered)
     * @param color	color4u used to fill the circle
     */
    void fillCircle(float radius, vec2f origin, color4u color);
    
    /**
     * Uploads the "buffer" texture to the GPU (effectively creating an SDL_Texture)
     */
    void apply(); // Apply everything
};

template <typename T> int sign(T val) { // TODO: Do something with this, this is not the right place for this function. lol
    return (T(0) < val) - (val < T(0));
}

RKT_NAMESPACE_END
#endif /* DrawTexture_hpp */
