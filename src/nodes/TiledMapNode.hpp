//
// Sprite.hpp
// Tom Albrecht, 06.12.15 - 01:13
// (Copyright)
//

#ifndef _TiledMapNode
#define _TiledMapNode 1

#include "SDL.h"
#include "SDL_image.h"
#include "tmxparser.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Sprite.hpp"
#include "Types.hpp"

FE_NAMESPACE_BEGIN

class TiledMapNode;
FE_create_Ptr(TiledMapNode);
typedef std::vector< Rect > RectVector;

/**
 * Loads and Displays a tiled tmx map
 */
class TiledMapNode : public Sprite {
public:
    /**
     * Creates a new TiledMapNode object
     *
     * @return a shared_ptr to the new TiledMapNode instance
     */
    static TiledMapNodePtr create(const std::string &filepath);
    
    /**
     * Deconstructor
     */
    ~TiledMapNode();
    
    // May return NULL if not found!
    SpritePtr getLayerNamed(std::string);
    
    // May return NULL if not found!
    tmxparser::TmxObjectGroup getObjectGroupNamed(std::string name);
    
    /** Gets raw TmxMap data from tmxparser */
    tmxparser::TmxMap getRawMap();
    
protected:
    bool init (const std::string &filepath);
private:
    std::string directory = ""; // path of directory the map is located in, in order to load images correctly
    void drawTiles();
    void getObjects();
    tmxparser::TmxMap map;
    std::vector<SpriteWeakPtr> mTileLayer;
};

} // namespace FE
#endif
