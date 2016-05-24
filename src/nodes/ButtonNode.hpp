//
//  ButtonNode.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 23.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
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

FE_NAMESPACE_BEGIN

class ButtonNode;
#define ButtonNodeLambda [this](ButtonNode *sender)
FE_create_Ptr(ButtonNode);
typedef std::function<void(ButtonNode*)> ButtonNodeCallback;

/**
 * Clickable LabelNode
 * NOTE: If there are textures for the states set,
 * they wil be used instead of rendered text
 */
class ButtonNode : public LabelNode {
public:
    static ButtonNodePtr create();
    static ButtonNodePtr create(std::string text, std::string fontpath, int fontSize);
    static ButtonNodePtr create(std::string text, std::string fontpath, int fontSize, Color col);
    static ButtonNodePtr create(TexturePtr normalTexture);
    static ButtonNodePtr create(TexturePtr normalTexture, TexturePtr selectedTexture);
    ~ButtonNode();
    
    void setHoverColor(Color hoverColor);
    Color getHoverColor();
    
    void setNormalColor(Color normalColor);
    Color getNormalColor();
    
    void setSelectedColor(Color selectedColor);
    Color getSelectedColor();
    
    
    void setNormalTexture(TexturePtr texture);
    TexturePtr getNormalTexture();
    
    void setHoverTexture(TexturePtr texture);
    TexturePtr getHoverTexture();

    void setSelectedTexture(TexturePtr texture);
    TexturePtr getSelectedTexture();
    
    
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
    bool init(TexturePtr normalTexture);
    bool init(TexturePtr normalTexture, TexturePtr selectedTexture);
    
    bool m_hovered = false;
    bool m_selected = false;
    
    Color m_HoverColor = ColorWhiteColor();
    Color m_SelectedColor = ColorGrayColor();
    Color m_NormalColor = ColorBlackColor();
    
    TexturePtr m_normalTexture;
    TexturePtr m_hoverTexture;
    TexturePtr m_selectTexture;
    
    ButtonNodeCallback m_CallbackDown = NULL;
    ButtonNodeCallback m_CallbackUp = NULL;
};

} // namespace FE
#endif /* ButtonNode_hpp */
