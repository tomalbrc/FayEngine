//
//  ButtonNode.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 23.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "ButtonNode.hpp"

ButtonNodePtr ButtonNode::create(std::string s) {
    ButtonNodePtr p(new ButtonNode());
    p->init(s);
    return p;
}
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



bool ButtonNode::init(std::string s) {
    if (LabelNode::init()) {
        setText(s);
        return true;
    }
    return false;
}
bool ButtonNode::init(std::string text, std::string fontpath, int fontSize, Color col) {
    return LabelNode::init(text,fontpath,fontSize, col);
}

ButtonNode::~ButtonNode() {
    m_CallbackUp = NULL;
    m_CallbackDown = NULL;
}



void ButtonNode::mouseClickBegan(SDL_MouseButtonEvent event, Vec2 coords) {
    auto bb = getBoundingBox();
    bb.origin = bb.origin - Vec2Make(getSize().x*getAnchorPoint().x, getSize().y*getAnchorPoint().y);
    if (RectIntersectsVec2(bb, convertToNodeSpace(coords))) {
        if (m_CallbackDown != nullptr) m_CallbackDown(this);
    }
}

void ButtonNode::mouseClickEnded(SDL_MouseButtonEvent event, Vec2 coords) {
    auto bb = getBoundingBox();
    bb.origin = bb.origin - Vec2Make(getSize().x*getAnchorPoint().x, getSize().y*getAnchorPoint().y);
    if (RectIntersectsVec2(bb, convertToNodeSpace(coords))) {
        if (m_CallbackUp != nullptr) m_CallbackUp(this);
    }
    setTextColor(m_NormalColor);
}

void ButtonNode::mouseMoved(SDL_MouseMotionEvent, Vec2 coords) {
    auto bb = getBoundingBox();
    bb.origin = bb.origin - Vec2Make(getSize().x*getAnchorPoint().x, getSize().y*getAnchorPoint().y);
    if (RectIntersectsVec2(bb, convertToNodeSpace(coords))) {
        if (m_HoverColor != getTextColor()) setTextColor(m_HoverColor);
    } else if (m_NormalColor != getTextColor()) setTextColor(m_NormalColor);
}




void ButtonNode::setSelected(bool selected) {
    m_selected = selected;
    if (selected) setTextColor(m_SelectedColor);
    else setTextColor(m_NormalColor);
}
bool ButtonNode::isSelected() {
    return m_hovered;
}

void ButtonNode::setHovered(bool hovered) {
    m_hovered = hovered;
    if (hovered) setTextColor(m_HoverColor);
    else setTextColor(m_NormalColor);
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

