//
//  ButtonNode.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 23.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "ButtonNode.hpp"

FE_NAMESPACE_BEGIN

ButtonNodePtr ButtonNode::create(std::string text, std::string fontpath, int fontSize) {
    ButtonNodePtr p(new ButtonNode());
    p->init(text,fontpath,fontSize, p->m_NormalColor);
    return p;
}
ButtonNodePtr ButtonNode::create(std::string text, std::string fontpath, int fontSize, Color col) {
    ButtonNodePtr p(new ButtonNode());
    p->init(text,fontpath,fontSize, col);
    return p;
}


ButtonNodePtr ButtonNode::create(TexturePtr normalTexture) {
    ButtonNodePtr p(new ButtonNode());
    p->init(normalTexture);
    return p;
}
ButtonNodePtr ButtonNode::create(TexturePtr normalTexture, TexturePtr selectedTexture) {
    ButtonNodePtr p(new ButtonNode());
    p->init(normalTexture, selectedTexture);
    return p;
}



bool ButtonNode::init(std::string text, std::string fontpath, int fontSize, Color col) {
    return LabelNode::init(text,fontpath,fontSize, col);
}

bool ButtonNode::init(TexturePtr normalTexture) {
    m_normalTexture = normalTexture;
    setTexture(normalTexture);
    return Sprite::init();
}

bool ButtonNode::init(TexturePtr normalTexture, TexturePtr selectedTexture) {
    m_normalTexture = normalTexture;
    m_selectTexture = selectedTexture;
    setTexture(normalTexture);
    return Sprite::init();
}


ButtonNode::~ButtonNode() {
    m_CallbackUp = NULL;
    m_CallbackDown = NULL;
}



void ButtonNode::mouseClickBegan(SDL_MouseButtonEvent event, Vec2 coords) {
    auto bb = getBoundingBox();
    bb.origin = bb.origin - Vec2Make(getSize().x*getAnchorPoint().x, getSize().y*getAnchorPoint().y);
    if (RectIntersectsVec2(bb, convertToNodeSpace(coords))) {
        setSelected(true);
        if (m_CallbackDown != nullptr) m_CallbackDown(this);
    } else setSelected(false);
}

void ButtonNode::mouseClickEnded(SDL_MouseButtonEvent event, Vec2 coords) {
    auto bb = getBoundingBox();
    bb.origin = bb.origin - Vec2Make(getSize().x*getAnchorPoint().x, getSize().y*getAnchorPoint().y);
    if (RectIntersectsVec2(bb, convertToNodeSpace(coords))) {
        if (m_CallbackUp != nullptr) m_CallbackUp(this);
    }
    setSelected(false);
}

void ButtonNode::mouseMoved(SDL_MouseMotionEvent, Vec2 coords) {
    auto bb = getBoundingBox();
    bb.origin = bb.origin - Vec2Make(getSize().x*getAnchorPoint().x, getSize().y*getAnchorPoint().y);
    if (RectIntersectsVec2(bb, convertToNodeSpace(coords))) {
        if (m_HoverColor != getTextColor()) setHovered(true);
    } else if (m_NormalColor != getTextColor()) setHovered(false);
}




void ButtonNode::setSelected(bool selected) {
    m_selected = selected;
    if (selected) setTextColor(m_SelectedColor);
    else setTextColor(m_NormalColor);
    
    if (selected && m_selectTexture) setTexture(m_selectTexture);
    else if (!selected && m_normalTexture) setTexture(m_normalTexture);
}
bool ButtonNode::isSelected() {
    return m_hovered;
}

void ButtonNode::setHovered(bool hovered) {
    m_hovered = hovered;
    if (hovered) setTextColor(m_HoverColor);
    else setTextColor(m_NormalColor);
    
    if (hovered && m_hoverTexture) setTexture(m_hoverTexture);
    else if (!hovered && m_normalTexture) setTexture(m_normalTexture);
}
bool ButtonNode::isHovered() {
    return m_hovered;
}



void ButtonNode::setPressedHandler(ButtonNodeCallback callback) {
    m_CallbackDown = callback;
}
ButtonNodeCallback ButtonNode::getPressedHandler() {
    return m_CallbackDown;
}


void ButtonNode::setReleasedHandler(ButtonNodeCallback callback) {
    m_CallbackUp = callback;
}
ButtonNodeCallback ButtonNode::getReleasedHandler() {
    return m_CallbackUp;
}


void ButtonNode::setHoverColor(Color hoverColor) {
    m_HoverColor = hoverColor;
}
Color ButtonNode:: getHoverColor() {
    return m_HoverColor;
}


void ButtonNode::setSelectedColor(Color selectedColor) {
    m_SelectedColor = selectedColor;
}
Color ButtonNode::getSelectedColor() {
    return m_SelectedColor;
}


void ButtonNode::setNormalColor(Color normalColor) {
    m_NormalColor = normalColor;
    SDL_MouseMotionEvent e;
    mouseMoved(e, Vec2Null());
}
Color ButtonNode:: getNormalColor() {
    return m_NormalColor;
}






void ButtonNode::setNormalTexture(TexturePtr texture) {
    m_normalTexture = texture;
    setTexture(texture); // TODO
}

TexturePtr ButtonNode::getNormalTexture() {
    return m_normalTexture;
}


void ButtonNode::setHoverTexture(TexturePtr texture) {
    m_hoverTexture = texture;
}

TexturePtr ButtonNode::getHoverTexture() {
    return m_hoverTexture;
}


void ButtonNode::setSelectedTexture(TexturePtr texture) {
    m_selectTexture = texture;
}

TexturePtr ButtonNode::getSelectedTexture() {
    return m_selectTexture;
}



FE_NAMESPACE_END
