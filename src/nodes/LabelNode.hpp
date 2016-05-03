//
//  LabelSprite.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 08.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef LabelSprite_hpp
#define LabelSprite_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Sprite.hpp"
#include "Types.hpp"

class LabelNode;
FE_create_Ptr(LabelNode);

/**
 * Display a string using an TTF font
 */
class LabelNode : public Sprite {
public:
    static LabelNodePtr create();
    static LabelNodePtr create(std::string text, std::string fontpath, int fontSize);
    static LabelNodePtr create(std::string text, std::string fontpath, int fontSize, Color col);
    ~LabelNode();
    
    void setText(std::string text);
    std::string getText();
    
    void setTextColor(Color col);
    Color getTextColor();
    
    void setFontPath(std::string fp);
    
    void setFontSize(int fs);
    int getFontSize();
    
    
protected:
    bool init();
    bool init(std::string text, std::string fontpath, int fontSize, Color col);
    void renderText();
private:
    TTF_Font *mFont = NULL;
    std::string mFontPath = "";
    Color mTextColor = ColorWhiteColor();
    std::string mText = "";
    int mFontSize = 24;
};

#endif /* LabelSprite_hpp */
