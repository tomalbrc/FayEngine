//
//  DrawTexture.cpp
//  rawket
//
//  Created by Tom Albrecht on 06.03.16.
//  
//

#include "DrawTexture.hpp"
#include "EngineHelper.hpp"

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

FE_NAMESPACE_BEGIN

void dt_plot(Vec2 p, SDL_Surface *s, Color col) {
    if (p.x < 0 || p.y < 0 || p.x > s->w || p.y > s->h) return;
    unsigned char* pixels = (unsigned char*)s->pixels;
    for (int c = 0; c < 4; c++) {
        pixels[int(4 * (p.y * s->w + p.x) + c)] = c == 0 ? col.b : c == 1 ? col.g : c == 2 ? col.r : col.a;
    }
}


DrawTexture::~DrawTexture() {
    SDL_FreeSurface(m_bufferSurface);
    SDL_DestroyTexture(mTexture);
}

DrawTexturePtr DrawTexture::create(Vec2 size, Color col) {
    std::stringstream s; s.str("");
    s << size.x << size.y << col.r << col.g << col.b << col.a << time(NULL) << rand();
    auto t = DrawTexturePtr(new DrawTexture());
    t->init(size,col);
    return t;
}




bool DrawTexture::init(Vec2 size, Color col) {
    m_bufferSurface = SDL_CreateRGBSurface(0, size.x, size.y, TEXTURE_BIT, rmask, gmask, bmask, amask);
    SDL_FillRect(m_bufferSurface, NULL, SDL_MapRGBA(m_bufferSurface->format, col.r, col.g, col.b, col.a));
    mTexture = SDL_CreateTextureFromSurface(EngineHelper::getInstance()->getRenderer(), m_bufferSurface);
    SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
    mSize = size;
    return true;
}



void DrawTexture::apply() {
    SDL_DestroyTexture(mTexture);
    mTexture = SDL_CreateTextureFromSurface(EngineHelper::getInstance()->getRenderer(), m_bufferSurface);
}

void DrawTexture::fillRect(Rect rect, Color col) {
    auto r = (SDL_Rect){(int)rect.origin.x,(int)rect.origin.y,(int)rect.size.x,(int)rect.size.y};
    SDL_FillRect(m_bufferSurface, &r, SDL_MapRGBA(m_bufferSurface->format, col.r, col.g, col.b, col.a));
}

void DrawTexture::fillEllipse(Rect rect, Color col) {
	auto origin = rect.origin + rect.size/2.0;
	auto width = rect.size.x/2.0;
	auto height = rect.size.y/2.0;

	for(int y=-height; y<=height; y++) {
		for(int x=-width; x<=width; x++) {
			double dx = (double)x / (double)width;
			double dy = (double)y / (double)height;
			if(dx*dx+dy*dy <= 1)
				dt_plot(Vec2Make(origin.x+x, origin.y+y), m_bufferSurface, col);
		}
	}
}



void DrawTexture::drawLine(Vec2 p1, Vec2 p2, Color color) {
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
			dt_plot(Vec2Make(y, x), m_bufferSurface, color);
		}
		else {
			dt_plot(Vec2Make(x, y), m_bufferSurface, color);
		}
 
		error -= dy;
		if(error < 0) {
			y += ystep;
			error += dx;
		}
	}
	SDL_LockSurface(m_bufferSurface);
}

void DrawTexture::fillCircle(float radius, Vec2 origin, Color color) {
    SDL_UnlockSurface(m_bufferSurface);
    for(int y=-radius; y<=radius; y++)
        for(int x=-radius; x<=radius; x++)
            if(x*x+y*y <= radius*radius)
                dt_plot(Vec2Make(origin.x+x, origin.y+y), m_bufferSurface, color);
    SDL_LockSurface(m_bufferSurface);
}

    
FE_NAMESPACE_END
