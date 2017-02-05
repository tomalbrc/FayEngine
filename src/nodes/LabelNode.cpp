//
//  LabelSprite.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 08.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "LabelNode.hpp"

FE_NAMESPACE_BEGIN

LabelNodePtr LabelNode::create() {
    LabelNodePtr p(new LabelNode());
    p->init();
    return p;
}
LabelNodePtr LabelNode::create(std::string text, std::string fontpath, int fontSize) {
    LabelNodePtr p(new LabelNode());
    p->init(text, fontpath, fontSize, p->mTextColor);
    return p;
}
LabelNodePtr LabelNode::create(std::string text, std::string fontpath, int fontSize, Color col) {
    LabelNodePtr p(new LabelNode());
    p->init(text, fontpath, fontSize, col);
    return p;
}


bool LabelNode::init() {
    return Sprite::init();
}
bool LabelNode::init(std::string text, std::string fontpath, int fontSize, Color col) {
    mTextColor = col;
    mFontSize = fontSize;
    setFontPath(fontpath);
    this->setText(text);
    return true;
}


LabelNode::~LabelNode() {
    TTF_CloseFont(mFont);
}


void LabelNode::setTextColor(Color col) {
    if (col.r == mTextColor.r && col.g == mTextColor.g && col.b == mTextColor.b && col.a == mTextColor.a) return;
    mTextColor = col;
    renderText();
}
Color LabelNode::getTextColor() {
    return mTextColor;
}


void LabelNode::renderText() {
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
    EngineHelper::getInstance()->removeTextureFromCache(getTexture());
    auto t = Texture::create(s);
    this->setTexture(t);
    SDL_FreeSurface(s);
    
    if (this->getTexture() == nullptr) FELog("LabelNode - Error: Texture is empty After new render" << SDL_GetError());
}


void LabelNode::setText(std::string text) {
    if (mText == text) return;
    mText = text;
    renderText();
}
    std::string LabelNode::getText() {
    return mText;
}



void LabelNode::setFontPath(std::string fp) {
    TTF_CloseFont(mFont);
    if (fp != mFontPath) {
        mFontPath = fp;
        mFont = TTF_OpenFont(fp.c_str(), mFontSize);
        renderText();
    }
}

void LabelNode::setFontSize(int fs) {
    if (fs == mFontSize) return;
    mFontSize = fs;
    renderText();
}
int LabelNode::getFontSize() {
    return mFontSize;
}
    
FE_NAMESPACE_END
