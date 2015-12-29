//
//  ButtonNode.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 23.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef ButtonNode_hpp
#define ButtonNode_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "tmxparser.h"
#include "LabelNode.hpp"

class ButtonNode;
#define ButtonNodeLambda [](ButtonNode *sender)
typedef std::function<void(ButtonNode*)> ButtonNodeCallback;
typedef std::shared_ptr<ButtonNode> ButtonNodePtr;

class ButtonNode : public LabelNode {
public:
    static ButtonNodePtr create(std::string text);
    static ButtonNodePtr create(std::string text, std::string fontpath, int fontSize);
    static ButtonNodePtr create(std::string text, std::string fontpath, int fontSize, Color col);
    ~ButtonNode();
    
    void setHoverColor(Color hoverColor);
    Color getHoverColor();
    
    void setNormalColor(Color normalColor);
    Color getNormalColor();
    
    void setHandler(ButtonNodeCallback callback);
    virtual void mouseClickBegan(SDL_MouseButtonEvent event, Vec2 coords);
    virtual void mouseMoved(SDL_MouseMotionEvent, Vec2 coords);
    
    
protected:
    bool init(std::string text);
    bool init(std::string text, std::string fontpath, int fontSize, Color col);
private:
    Color mHoverColor = ColorBlackColor();
    Color mNormalColor = ColorWhiteColor();
    ButtonNodeCallback mCallback = NULL;
};

#endif /* ButtonNode_hpp */
