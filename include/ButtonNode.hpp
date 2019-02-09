//
//  ButtonNode.hpp
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
#include "LabelNode.hpp"

RKT_NAMESPACE_BEGIN

class ButtonNode;
#define ButtonNodeLambda [this](ButtonNode *sender)
RKT_create__ptr(ButtonNode);
typedef std::function<void(ButtonNode*)> ButtonNodeCallback;

/**
 * Clickable LabelNode
 * NOTE: If there are textures for the states set,
 * they wil be used instead of rendered text
 */
class ButtonNode : public LabelNode {
public:
    static ButtonNode_ptr create();
    static ButtonNode_ptr create(std::string text, std::string fontpath, int fontSize);
    static ButtonNode_ptr create(std::string text, std::string fontpath, int fontSize, Color col);
    static ButtonNode_ptr create(Texture_ptr normalTexture);
    static ButtonNode_ptr create(Texture_ptr normalTexture, Texture_ptr selectedTexture);
    ~ButtonNode();
    
    void setHoverColor(Color hoverColor);
    Color getHoverColor();
    
    void setNormalColor(Color normalColor);
    Color getNormalColor();
    
    void setSelectedColor(Color selectedColor);
    Color getSelectedColor();
    
    
    void setNormalTexture(Texture_ptr texture);
    Texture_ptr getNormalTexture();
    
    void setHoverTexture(Texture_ptr texture);
    Texture_ptr getHoverTexture();

    void setSelectedTexture(Texture_ptr texture);
    Texture_ptr getSelectedTexture();
    
    
    void setSelected(bool selected);
    bool isSelected();
    
    void setHovered(bool hovered);
    bool isHovered();
    
    void setPressedHandler(ButtonNodeCallback callback);
    ButtonNodeCallback getPressedHandler();
    
    void setReleasedHandler(ButtonNodeCallback callback);
    ButtonNodeCallback getReleasedHandler();
    
    
    virtual void mouseClickBegan(SDL_MouseButtonEvent event, Vec2 coords);
    virtual void mouseClickEnded(SDL_MouseButtonEvent event, Vec2 coords);
    virtual void mouseMoved(SDL_MouseMotionEvent, Vec2 coords);
    
    
private:
    bool init();
    bool init(std::string text, std::string fontpath, int fontSize, Color col);
    bool init(Texture_ptr normalTexture);
    bool init(Texture_ptr normalTexture, Texture_ptr selectedTexture);
    
    bool m_hovered = false;
    bool m_selected = false;
    
    Color m_HoverColor = ColorWhiteColor();
    Color m_SelectedColor = ColorGrayColor();
    Color m_NormalColor = ColorBlackColor();
    
    Texture_ptr m_normalTexture;
    Texture_ptr m_hoverTexture;
    Texture_ptr m_selectTexture;
    
    ButtonNodeCallback m_CallbackDown = NULL;
    ButtonNodeCallback m_CallbackUp = NULL;
};

RKT_NAMESPACE_END
#endif /* ButtonNode_hpp */
