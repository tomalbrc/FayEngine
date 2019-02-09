//
//  button_node.cpp
//  rawket
//
//  Created by Tom Albrecht on 23.12.15.
//  
//

#include "button_node.hpp"

RKT_NAMESPACE_BEGIN

button_node_ptr button_node::create(std::string text, std::string fontpath, int fontSize) {
    button_node_ptr p(new button_node());
    p->init(text,fontpath,fontSize, p->m_NormalColor);
    return p;
}
button_node_ptr button_node::create(std::string text, std::string fontpath, int fontSize, color4u col) {
    button_node_ptr p(new button_node());
    p->init(text,fontpath,fontSize, col);
    return p;
}


button_node_ptr button_node::create(texture_ptr normalTexture) {
    button_node_ptr p(new button_node());
    p->init(normalTexture);
    return p;
}
button_node_ptr button_node::create(texture_ptr normalTexture, texture_ptr selectedTexture) {
    button_node_ptr p(new button_node());
    p->init(normalTexture, selectedTexture);
    return p;
}



bool button_node::init(std::string text, std::string fontpath, int fontSize, color4u col) {
    return label_node::init(text,fontpath,fontSize, col);
}

bool button_node::init(texture_ptr normalTexture) {
    m_normalTexture = normalTexture;
    setTexture(normalTexture);
    return sprite::init();
}

bool button_node::init(texture_ptr normalTexture, texture_ptr selectedTexture) {
    m_normalTexture = normalTexture;
    m_selectTexture = selectedTexture;
    setTexture(normalTexture);
    return sprite::init();
}


button_node::~button_node() {
    m_CallbackUp = NULL;
    m_CallbackDown = NULL;
}



void button_node::mouseClickBegan(SDL_MouseButtonEvent event, vec2f coords) {
    auto bb = getBoundingBox();
    bb.origin = bb.origin - vec2f_make(getSize().x*getAnchorPoint().x, getSize().y*getAnchorPoint().y);
    if (rect_intersects_vec2f(bb, convertToNodeSpace(coords))) {
        setSelected(true);
        if (m_CallbackDown != nullptr) m_CallbackDown(this);
    } else setSelected(false);
}

void button_node::mouseClickEnded(SDL_MouseButtonEvent event, vec2f coords) {
    auto bb = getBoundingBox();
    bb.origin = bb.origin - vec2f_make(getSize().x*getAnchorPoint().x, getSize().y*getAnchorPoint().y);
    if (rect_intersects_vec2f(bb, convertToNodeSpace(coords))) {
        if (m_CallbackUp != nullptr) m_CallbackUp(this);
    }
    setSelected(false);
}

void button_node::mouseMoved(SDL_MouseMotionEvent, vec2f coords) {
    auto bb = getBoundingBox();
    bb.origin = bb.origin - vec2f_make(getSize().x*getAnchorPoint().x, getSize().y*getAnchorPoint().y);
    if (rect_intersects_vec2f(bb, convertToNodeSpace(coords))) {
        if (m_HoverColor != getTextColor()) setHovered(true);
    } else if (m_NormalColor != getTextColor()) setHovered(false);
}




void button_node::setSelected(bool selected) {
    m_selected = selected;
    if (selected) setTextColor(m_SelectedColor);
    else setTextColor(m_NormalColor);
    
    if (selected && m_selectTexture) setTexture(m_selectTexture);
    else if (!selected && m_normalTexture) setTexture(m_normalTexture);
}
bool button_node::isSelected() {
    return m_hovered;
}

void button_node::setHovered(bool hovered) {
    m_hovered = hovered;
    if (hovered) setTextColor(m_HoverColor);
    else setTextColor(m_NormalColor);
    
    if (hovered && m_hoverTexture) setTexture(m_hoverTexture);
    else if (!hovered && m_normalTexture) setTexture(m_normalTexture);
}
bool button_node::isHovered() {
    return m_hovered;
}



void button_node::setPressedHandler(callback callback) {
    m_CallbackDown = callback;
}
button_node::callback button_node::getPressedHandler() {
    return m_CallbackDown;
}


void button_node::setReleasedHandler(callback callback) {
    m_CallbackUp = callback;
}
button_node::callback button_node::getReleasedHandler() {
    return m_CallbackUp;
}


void button_node::setHoverColor(color4u hoverColor) {
    m_HoverColor = hoverColor;
}
color4u button_node:: getHoverColor() {
    return m_HoverColor;
}


void button_node::setSelectedColor(color4u selectedColor) {
    m_SelectedColor = selectedColor;
}
color4u button_node::getSelectedColor() {
    return m_SelectedColor;
}


void button_node::setNormalColor(color4u normalColor) {
    m_NormalColor = normalColor;
    SDL_MouseMotionEvent e;
    mouseMoved(e, vec2f_null());
}
color4u button_node:: getNormalColor() {
    return m_NormalColor;
}






void button_node::setNormalTexture(texture_ptr texture) {
    m_normalTexture = texture;
    setTexture(texture); // TODO
}

texture_ptr button_node::getNormalTexture() {
    return m_normalTexture;
}


void button_node::setHoverTexture(texture_ptr texture) {
    m_hoverTexture = texture;
}

texture_ptr button_node::getHoverTexture() {
    return m_hoverTexture;
}


void button_node::setSelectedTexture(texture_ptr texture) {
    m_selectTexture = texture;
}

texture_ptr button_node::getSelectedTexture() {
    return m_selectTexture;
}



RKT_NAMESPACE_END
