//
//  sprite.cpp
//  rawket
//
//  Created by Tom Albrecht on 08.12.15.
//  
//

#include "sprite.hpp"
#include "scene.hpp"

RKT_NAMESPACE_BEGIN

sprite_ptr sprite::create() {
    sprite_ptr ss(new sprite());
    ss->init();
    return ss;
}
sprite_ptr sprite::create(texture_ptr s) {
    sprite_ptr ss(new sprite());
    ss->init(s);
    return ss;
}
sprite_ptr sprite::create(vec2f dimensions) {
    sprite_ptr ss(new sprite());
    ss->init(dimensions);
    return ss;
}
sprite_ptr sprite::create(std::string filename) {
    sprite_ptr ss(new sprite());
    ss->init(filename);
    return ss;
}

bool sprite::init() {
    return node::init();
}

bool sprite:: init(texture_ptr s) {
    if (node::init()) {
        setTexture(s);
        return true;
    }
    return false;
}
bool sprite:: init(vec2f dimensions) {
    if (node::init()) {
        setTexture(texture::create(vec2f_make(dimensions.x, dimensions.y), ColorWhiteColor()));
        return true;
    }
    return init();
}
bool sprite::init(std::string filename) {
    if (node::init()) {
        setTexture(texture::create(filename));
        return true;
    }
    return false;
}

sprite:: ~sprite() {
    mTexture.reset();
}





vec2f sprite::getSize() {
    return mSize;
}


void sprite::setTexture(texture_ptr tex) {
    mTexture.reset();
    mTexture = tex;
    if (tex != nullptr) mSize = tex->getSize();
}
texture_ptr sprite::getTexture() {
    return mTexture;
}



BlendMode sprite::getBlendMode() {
    return m_blendMode;
}

void sprite::setBlendMode(BlendMode mode) {
    m_blendMode = mode;
}




// rectangle in parent coordinate system
rectangle sprite::getRect() {
    return rect_make(getPosition() - (getAnchorPoint()*getSize()), getSize()*getScale());
}

// rectangle in own coordinate system
rectangle sprite::getBoundingBox() {
    return rect_make(vec2f_null(), getSize());
}




void sprite::render(SDL_Renderer *renderer) { // render into scene / Surfac
    if (this->getTexture() != nullptr) { // Draw this sprite if the tex is set
        auto absRot = getZRotation();
        auto absScale = getScale();
        for (auto p = getParent(); p.get() != NULL; p = p->getParent()) {
            absScale = absScale * p->getScale(), absRot += p->getZRotation();
        }
        
        auto sRect = rect_make(mTexture->getRenderOffset(), mTexture->getSize());
        auto dRect = rect_make(convertToWorldSpace(vec2f_null()), getSize()*absScale);
        
        dRect = dRect*engine_helper::getInstance()->getMainWindow()->screenScale();
        
        SDL_Rect ddRect;
        ddRect.x = dRect.origin.x, ddRect.y = dRect.origin.y, ddRect.w = dRect.size.x, ddRect.h = dRect.size.y;
        ddRect.x -= getAnchorPoint().x * ddRect.w;
        ddRect.y -= getAnchorPoint().y * ddRect.h;
        
        // Culling // UPDATE: Probably not neccesary as the GPU already culls triangles and a texture are 2 tris (guesstimated (assuming tris is short for triangles)
        // Also, there's a problem with rotation not taken into account :O
        //auto s = this->getScene()->getWindow()->getSize()*(engine_helper::getInstance()->getMainWindow()->screenScale());
        //if (rectangles_intersect(rect_make(ddRect.x, ddRect.y, ddRect.w, ddRect.h), rect_make(vec2f_null(), s))) {
            
            SDL_Rect ssRect;
            ssRect.x = sRect.origin.x, ssRect.y = sRect.origin.y, ssRect.w = sRect.size.x, ssRect.h = sRect.size.y;
            
            SDL_Point center;
            center.x = ddRect.w*getAnchorPoint().x;
            center.y = ddRect.h*getAnchorPoint().y;
        
        // Apply sprite properties to SDL_Texture
            SDL_SetTextureColorMod(mTexture->sdlTexture(), m_color.r, m_color.g, m_color.b);
            SDL_SetTextureBlendMode(mTexture->sdlTexture(), SDL_BlendMode(m_blendMode));
            SDL_SetTextureAlphaMod(mTexture->sdlTexture(), getAlpha());
        
            SDL_RenderCopyEx(renderer, mTexture->sdlTexture(), &ssRect, &ddRect, -RadiansToDegrees(absRot), &center, SDL_FLIP_NONE);
        //}
    }
    node::render(renderer);
}




void sprite::setColor(color4u color) {
    m_color = color;
}
color4u sprite::getColor() {
    return m_color;
}

    
RKT_NAMESPACE_END
