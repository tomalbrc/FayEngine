//
//  LabelSprite.hpp
//  rawket
//
//  Created by Tom Albrecht on 08.12.15.
//  
//

#ifndef LabelSprite_hpp
#define LabelSprite_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Sprite.hpp"
#include "Types.hpp"

RKT_NAMESPACE_BEGIN

class LabelNode;
RKT_create__ptr(LabelNode);

/**
 * Display a string using an TTF font
 */
class LabelNode : public Sprite {
public:
    /**
     * Create an empty label node, not font or text set
     */
    static LabelNode_ptr create();

	/**
	 * Returns a new LabelNode with text, font and fontsize. Color is white by default
	 *
	 * @param text	Text to display
	 * @param fontpath	Path to the font file used to display the text
	 * @param	fontSize	Size of the text
	 */
    static LabelNode_ptr create(std::string text, std::string fontpath, int fontSize);

	/**
	 * See above.
	 *
	 * @param col color of the text
	 */
    static LabelNode_ptr create(std::string text, std::string fontpath, int fontSize, Color col);

    ~LabelNode();

	/**
	 * Set new text
	 *
	 * @param text	New Text to display
	 */
    void setText(std::string text);
    
	/**
	 * Returns the current text of the LabelNode
	 */
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

RKT_NAMESPACE_END
#endif /* LabelSprite_hpp */
