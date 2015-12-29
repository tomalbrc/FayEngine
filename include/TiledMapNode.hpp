//
// Sprite.hpp
// Tom Albrecht, 06.12.15 - 01:13
// (Copyright)
//

#ifndef _TiledMapNode
#define _TiledMapNode 1

#include <SDL.h>
#include <SDL_image.h>
#include "tmxparser.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Sprite.hpp"

class TiledMapNode;
typedef std::shared_ptr<TiledMapNode> TiledMapNodePtr;
typedef std::vector< Rect > RectVector;

class TiledMapNode : public Sprite {
public:
    static TiledMapNodePtr create(const std::string &filepath);
    ~TiledMapNode();
    
    RectVector walls;
    RectVector mobSpawns;
    
    // May return NULL if not found!
    SpritePtr getLayerNamed(std::string);
    
    // Gets raw TmxMap data
    tmxparser::TmxMap *getRawMap();
    
    
protected:
    bool init (const std::string &filepath);
private:
    void drawTiles();
    void getObjects();
    tmxparser::TmxMap *map;
    std::map<std::string, SpritePtr> layers;
};


#endif
