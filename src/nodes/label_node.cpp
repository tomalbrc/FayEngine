//
//  LabelSprite.cpp
//  rawket
//
//  Created by Tom Albrecht on 08.12.15.
//  
//

#include "label_node.hpp"

RKT_NAMESPACE_BEGIN

label_node_ptr label_node::create() {
    label_node_ptr p(new label_node());
    p->init();
    return p;
}
label_node_ptr label_node::create(std::string text, std::string fontpath, int fontSize) {
    label_node_ptr p(new label_node());
    p->init(text, fontpath, fontSize, p->mTextColor);
    return p;
}
label_node_ptr label_node::create(std::string text, std::string fontpath, int fontSize, color4u col) {
    label_node_ptr p(new label_node());
    p->init(text, fontpath, fontSize, col);
    return p;
}


bool label_node::init() {
    return sprite::init();
}
bool label_node::init(std::string text, std::string fontpath, int fontSize, color4u col) {
    mTextColor = col;
    mFontSize = fontSize;
    setFontPath(fontpath);
    this->setText(text);
    return true;
}


label_node::~label_node() {
    TTF_CloseFont(mFont);
}


void label_node::setTextColor(color4u col) {
    if (col.r == mTextColor.r && col.g == mTextColor.g && col.b == mTextColor.b && col.a == mTextColor.a) return;
    mTextColor = col;
    renderText();
}
color4u label_node::getTextColor() {
    return mTextColor;
}


void label_node::renderText() {
    if (mFont == nullptr || mText.empty()) {
        setTexture(NULL);
        return;
    }

    SDL_Color c;
    c.r = mTextColor.r;
    c.g = mTextColor.g;
    c.b = mTextColor.b;
    c.a = mTextColor.a;
    
    SDL_Surface *s = TTF_RenderText_Blended(mFont, mText.c_str(), c);
    engine_helper::getInstance()->removeTextureFromCache(getTexture());
    auto t = texture::create(s);
    this->setTexture(t);
    SDL_FreeSurface(s);
    
    if (this->getTexture() == nullptr) RKTLog("label_node - Error: texture is empty After new render" << SDL_GetError());
}


void label_node::setText(std::string text) {
    if (mText == text) return;
    mText = text;
    renderText();
}
    std::string label_node::getText() {
    return mText;
}



void label_node::setFontPath(std::string fp) {
    TTF_CloseFont(mFont);
    if (fp != mFontPath) {
        mFontPath = fp;
        mFont = TTF_OpenFont(fp.c_str(), mFontSize);
        renderText();
    }
}

void label_node::setFontSize(int fs) {
    if (fs == mFontSize) return;
    mFontSize = fs;
    renderText();
}
int label_node::getFontSize() {
    return mFontSize;
}
    
RKT_NAMESPACE_END
