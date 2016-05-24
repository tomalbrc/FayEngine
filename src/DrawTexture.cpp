//
//  DrawTexture.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 06.03.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
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

void dt_plot(Vec2 p, SDL_Surface *s, Color col) {
    for (int c = 0; c < 4; c++) {
        unsigned char* pixels = (unsigned char*)s->pixels;
        pixels[int(4 * (p.y * s->w + p.x) + c)] = c == 0 ? col.b : c == 1 ? col.g : c == 2 ? col.r : col.a;
    }
}

void DrawTexture::drawLine(Vec2 p1, Vec2 p2, Color color) {
    if (p1.x > p2.x) {
        auto b = p2;
        p2 = p1;
        p1 = b;
    }
    
    SDL_UnlockSurface(m_bufferSurface);
    float error = 0.f;
    auto deltax = p2.x - p1.x;
    auto deltay = p2.y - p1.y;
    auto deltaerr = fabs(deltay / deltax);    // Assume deltax != 0 (line is not vertical),
    auto y = p1.y;
    for (auto x = p1.x; x < p2.x; x++) {
        dt_plot(Vec2Make(x, y), m_bufferSurface, color);
        error += deltaerr;
        while (error >= 0.5) {
            dt_plot(Vec2Make(x, y), m_bufferSurface, color);
            y += sign(p2.y - p1.y);
            error -= 1.0;
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

    
} // namespace FE
