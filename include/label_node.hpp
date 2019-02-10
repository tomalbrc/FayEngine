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
#include "sprite.hpp"
#include "types.hpp"

RKT_NAMESPACE_BEGIN

class label_node;
rkt_create_ptr(label_node);

/**
 * Display a string using an TTF font
 */
class label_node : public sprite {
public:
    /**
     * Create an empty label node, not font or text set
     */
    static label_node_ptr create();

	/**
	 * Returns a new label_node with text, font and fontsize. color4u is white by default
	 *
	 * @param text	Text to display
	 * @param fontpath	Path to the font file used to display the text
	 * @param	fontSize	Size of the text
	 */
    static label_node_ptr create(std::string text, std::string fontpath, int fontSize);

	/**
	 * See above.
	 *
	 * @param col color of the text
	 */
    static label_node_ptr create(std::string text, std::string fontpath, int fontSize, color4u col);

    ~label_node();

	/**
	 * Set new text
	 *
	 * @param text	New Text to display
	 */
    void setText(std::string text);
    
	/**
	 * Returns the current text of the label_node
	 */
    std::string getText();

    void setTextColor(color4u col);
    color4u getTextColor();

    void setFontPath(std::string fp);

    void setFontSize(int fs);
    int getFontSize();

protected:
    bool init();
    bool init(std::string text, std::string fontpath, int fontSize, color4u col);
    void renderText();
private:
    TTF_Font *mFont = NULL;
    std::string mFontPath = "";
    color4u mTextColor = ColorWhiteColor();
    std::string mText = "";
    int mFontSize = 24;
};

RKT_NAMESPACE_END
#endif /* LabelSprite_hpp */
