//
//  draw_texture.cpp
//  rawket
//
//  Created by Tom Albrecht on 06.03.16.
//  
//

#include "draw_texture.hpp"
#include "engine_helper.hpp"

#define ALPHA_COLOR_KEY 3
#define RED_COLOR_KEY 2
#define GREEN_COLOR_KEY 1
#define BLUE_COLOR_KEY 0

#define TEXTURE_BIT 32

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000
#define gmask 0x00ff0000
#define bmask 0x0000ff00
#define amask 0x000000ff
#else
#define rmask 0x000000ff
#define gmask 0x0000ff00
#define bmask 0x00ff0000
#define amask 0xff000000
#endif

RKT_NAMESPACE_BEGIN

void dt_plot(vec2f p, SDL_Surface *s, color4u col) {
    if (p.x < 0 || p.y < 0 || p.x > s->w || p.y > s->h) return;
    unsigned char* pixels = (unsigned char*)s->pixels;
    for (int c = 0; c < 4; c++) {
        pixels[int(4 * (p.y * s->w + p.x) + c)] = c == 0 ? col.b : c == 1 ? col.g : c == 2 ? col.r : col.a;
    }
}


draw_texture::~draw_texture() {
    SDL_FreeSurface(m_bufferSurface);
    SDL_DestroyTexture(mTexture);
}

draw_texture_ptr draw_texture::create(vec2f size, color4u col) {
    std::stringstream s; s.str("");
    s << size.x << size.y << col.r << col.g << col.b << col.a << time(NULL) << rand();
    auto t = draw_texture_ptr(new draw_texture());
    t->init(size,col);
    return t;
}




bool draw_texture::init(vec2f size, color4u col) {
    m_bufferSurface = SDL_CreateRGBSurface(0, size.x, size.y, TEXTURE_BIT, rmask, gmask, bmask, amask);
    SDL_FillRect(m_bufferSurface, NULL, SDL_MapRGBA(m_bufferSurface->format, col.r, col.g, col.b, col.a));
    mTexture = SDL_CreateTextureFromSurface(engine_helper::getInstance()->getRenderer(), m_bufferSurface);
    SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
    mSize = size;
    return true;
}



void draw_texture::apply() {
    SDL_DestroyTexture(mTexture);
    mTexture = SDL_CreateTextureFromSurface(engine_helper::getInstance()->getRenderer(), m_bufferSurface);
}

void draw_texture::fillRect(rectangle rectangle, color4u col) {
    auto r = (SDL_Rect){(int)rectangle.origin.x,(int)rectangle.origin.y,(int)rectangle.size.x,(int)rectangle.size.y};
    SDL_FillRect(m_bufferSurface, &r, SDL_MapRGBA(m_bufferSurface->format, col.r, col.g, col.b, col.a));
}

void draw_texture::fillEllipse(rectangle rectangle, color4u col) {
	auto origin = rectangle.origin + rectangle.size/2.0;
	auto width = rectangle.size.x/2.0;
	auto height = rectangle.size.y/2.0;

	for(int y=-height; y<=height; y++) {
		for(int x=-width; x<=width; x++) {
			double dx = (double)x / (double)width;
			double dy = (double)y / (double)height;
			if(dx*dx+dy*dy <= 1)
				dt_plot(vec2f_make(origin.x+x, origin.y+y), m_bufferSurface, col);
		}
	}
}



void draw_texture::drawLine(vec2f p1, vec2f p2, color4u color) {
	// Bresenham's line algorithm
	auto x1 = p1.x;
	auto y1 = p1.y;
	auto x2 = p2.x;
	auto y2 = p2.y;
	
	SDL_UnlockSurface(m_bufferSurface);
	
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if( steep) {
		std::swap(x1, y1);
		std::swap(x2, y2);
	}
 
	if(x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
 
	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);
 
	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;
 
	const int maxX = (int)x2;
 
	for(int x=(int)x1; x<maxX; x++) {
		if(steep) {
			dt_plot(vec2f_make(y, x), m_bufferSurface, color);
		}
		else {
			dt_plot(vec2f_make(x, y), m_bufferSurface, color);
		}
 
		error -= dy;
		if(error < 0) {
			y += ystep;
			error += dx;
		}
	}
	SDL_LockSurface(m_bufferSurface);
}

void draw_texture::fillCircle(float radius, vec2f origin, color4u color) {
    SDL_UnlockSurface(m_bufferSurface);
    for(int y=-radius; y<=radius; y++)
        for(int x=-radius; x<=radius; x++)
            if(x*x+y*y <= radius*radius)
                dt_plot(vec2f_make(origin.x+x, origin.y+y), m_bufferSurface, color);
    SDL_LockSurface(m_bufferSurface);
}

    
RKT_NAMESPACE_END
