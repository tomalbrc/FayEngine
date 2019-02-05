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
#include "Node.hpp"
#include "Sprite.hpp"
#include "Types.hpp"

FE_NAMESPACE_BEGIN

class TiledMapNode2;
FE_create_Ptr(TiledMapNode2);
typedef std::vector< Rect > RectVector;

/**
 * Loads and Displays a tiled tmx map
 */
class TiledMapNode2 : public Node {
public:
    /**
     * Creates a new TiledMapNode object
     *
     * @return a shared_ptr to the new TiledMapNode instance
     */
    static TiledMapNode2Ptr create(const std::string &filepath);
    
    /**
     * Deconstructor
     */
    ~TiledMapNode2();
    
    /**
     * Returns all tile layers in a vector (as std::weak_ptr<Sprites>)
     */
    const std::vector<NodePtr> getAllLayers();
    
    /// May return NULL if not found!
    const NodePtr getLayerNamed(std::string);
    
    const std::vector<tmxparser::TmxObjectGroup> getAllObjectGroups();
    
    /// May return NULL if not found!
    const tmxparser::TmxObjectGroup getObjectGroupNamed(std::string name);
    
    /**
     * Sets the anchorPoint of all layers
     */
    virtual void setAnchorPoint(FE::Vec2 ap);
    
    /**
     * Gets raw TmxMap data from tmxparser 
     */
    const tmxparser::TmxMap getRawMap();
    
    /**
     * Size of the whole map (horizontal tile count * tile size, vertical tile count * tile size)
     */
    virtual const Vec2 getSize();
    
    /**
     * Position, taking the anchorPoint into account
     */
    virtual const Vec2 getPosition();
    
    
protected:
    bool init (const std::string &filepath);
private:
    std::string directory = ""; // path of directory the map is located in, in order to load images correctly
    void drawTiles();
    void getObjects();
    tmxparser::TmxMap map;
    std::vector<NodePtr> mTileLayer;
};

FE_NAMESPACE_END
#endif
