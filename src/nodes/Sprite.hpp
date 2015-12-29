//
// Sprite.hpp
// Tom Albrecht, 06.12.15 - 01:13
// (Copyright)
//

#ifndef SPRITE
#define SPRITE 1


#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Node.hpp"
#include "Texture.hpp"
#include "EngineHelper.hpp"

enum Direction {
    None,
    Up,
    Right,
    Down,
    Left,
};

class Sprite;
typedef std::shared_ptr<Sprite> SpritePtr;
typedef std::weak_ptr<Sprite> SpriteWeakPtr;

class Sprite : public Node {
public:
    bool init();
    bool init(TexturePtr texture);
    bool init(Vec2 dimensions); // empty sprite
    bool init(std::string filename); // load sprite with texture from filename
    static SpritePtr create();
    static SpritePtr create(TexturePtr t);
    static SpritePtr create(Vec2 dimensions);
    static SpritePtr create(std::string filename);
    ~Sprite();

    Vec2 getSize();
    
    void setTexture(TexturePtr tex);
    TexturePtr getTexture();
    
    void setAnchorPoint(Vec2 ap);
    Vec2 getAnchorPoint();
    
    Rect getRect();
    Rect getBoundingBox();
    
    void render(SDL_Renderer *renderer);
    
private:
    Vec2 mSize = Vec2Null();
    Vec2 mAnchorPoint = Vec2Null();
    TexturePtr mTexture = NULL;
};



#endif