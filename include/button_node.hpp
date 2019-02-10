//
//  button_node.hpp
//  rawket
//
//  Created by Tom Albrecht on 23.12.15.
//  
//

#ifndef ButtonNode_hpp
#define ButtonNode_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "tmxparser.h"
#include "label_node.hpp"

RKT_NAMESPACE_BEGIN

class button_node;
#define ButtonNodeLambda [this](button_node *sender)
rkt_create_ptr(button_node);

/**
 * Clickable label_node
 * NOTE: If there are textures for the states set,
 * they wil be used instead of rendered text
 */
class button_node : public label_node {
public:
    typedef std::function<void(button_node*)> callback;

    static button_node_ptr create();
    static button_node_ptr create(std::string text, std::string fontpath, int fontSize);
    static button_node_ptr create(std::string text, std::string fontpath, int fontSize, color4u col);
    static button_node_ptr create(texture_ptr normalTexture);
    static button_node_ptr create(texture_ptr normalTexture, texture_ptr selectedTexture);
    ~button_node();
    
    void setHoverColor(color4u hoverColor);
    color4u getHoverColor();
    
    void setNormalColor(color4u normalColor);
    color4u getNormalColor();
    
    void setSelectedColor(color4u selectedColor);
    color4u getSelectedColor();
    
    
    void setNormalTexture(texture_ptr texture);
    texture_ptr getNormalTexture();
    
    void setHoverTexture(texture_ptr texture);
    texture_ptr getHoverTexture();

    void setSelectedTexture(texture_ptr texture);
    texture_ptr getSelectedTexture();
    
    
    void setSelected(bool selected);
    bool isSelected();
    
    void setHovered(bool hovered);
    bool isHovered();
    
    void setPressedHandler(callback callback);
    callback getPressedHandler();
    
    void setReleasedHandler(callback callback);
    callback getReleasedHandler();
    
    
    virtual void mouseClickBegan(SDL_MouseButtonEvent event, vec2f coords);
    virtual void mouseClickEnded(SDL_MouseButtonEvent event, vec2f coords);
    virtual void mouseMoved(SDL_MouseMotionEvent, vec2f coords);
    
    
private:
    bool init();
    bool init(std::string text, std::string fontpath, int fontSize, color4u col);
    bool init(texture_ptr normalTexture);
    bool init(texture_ptr normalTexture, texture_ptr selectedTexture);
    
    bool m_hovered = false;
    bool m_selected = false;
    
    color4u m_HoverColor = ColorWhiteColor();
    color4u m_SelectedColor = ColorGrayColor();
    color4u m_NormalColor = ColorBlackColor();
    
    texture_ptr m_normalTexture;
    texture_ptr m_hoverTexture;
    texture_ptr m_selectTexture;
    
    callback m_CallbackDown = NULL;
    callback m_CallbackUp = NULL;
};

RKT_NAMESPACE_END
#endif /* ButtonNode_hpp */
