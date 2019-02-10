//
// sprite.hpp
// Tom Albrecht, 06.12.15 - 01:13
//

#ifndef _TiledMapNode
#define _TiledMapNode 1

#include "SDL.h"
#include "SDL_image.h"
#include "tmxparser.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "node.hpp"
#include "sprite.hpp"
#include "types.hpp"

RKT_NAMESPACE_BEGIN

class tiled_map2;
rkt_create_ptr(tiled_map2);
typedef std::vector< rectangle > RectVector;

/**
 * Loads and Displays a tiled tmx map
 */
class tiled_map2 : public node {
public:
    /**
     * Creates a new tiled_map object
     *
     * @return a shared_ptr to the new tiled_map instance
     */
    static tiled_map2_ptr create(const std::string &filepath);
    
    /**
     * Deconstructor
     */
    ~tiled_map2();
    
    /**
     * Returns all tile layers in a vector (as std::weak_ptr<Sprites>)
     */
    const std::vector<node_ptr> getAllLayers();
    
    /// May return NULL if not found!
    const node_ptr getLayerNamed(std::string);
    
    const std::vector<tmxparser::TmxObjectGroup> getAllObjectGroups();
    
    /// May return NULL if not found!
    const tmxparser::TmxObjectGroup getObjectGroupNamed(std::string name);
    
    /**
     * Sets the anchorPoint of all layers
     */
    virtual void setAnchorPoint(rkt::vec2f ap);
    
    /**
     * Gets raw TmxMap data from tmxparser 
     */
    const tmxparser::TmxMap getRawMap();
    
    /**
     * Size of the whole map (horizontal tile count * tile size, vertical tile count * tile size)
     */
    virtual const vec2f getSize();
    
    /**
     * Position, taking the anchorPoint into account
     */
    virtual const vec2f getPosition();
    
    
protected:
    bool init (const std::string &filepath);
private:
    std::string directory = ""; // path of directory the map is located in, in order to load images correctly
    void drawTiles();
    void getObjects();
    tmxparser::TmxMap map;
    std::vector<node_ptr> mTileLayer;
};

RKT_NAMESPACE_END
#endif
