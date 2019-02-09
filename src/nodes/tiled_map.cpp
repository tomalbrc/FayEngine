//
//  tiled_map.cpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#include "tiled_map.hpp"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask  0xff000000
#define gmask  0x00ff0000
#define bmask  0x0000ff00
#define amask  0x000000ff
#else
#define rmask  0x000000ff
#define gmask  0x0000ff00
#define bmask  0x00ff0000
#define amask  0xff000000
#endif

RKT_NAMESPACE_BEGIN

tiled_map_ptr tiled_map::create(const std::string &filepath) {
    tiled_map_ptr p(new tiled_map());
    p->init(filepath);
    return p;
}

bool tiled_map::init(const std::string &filepath) {
    map = tmxparser::TmxMap();
    
    char *path = SDL_GetBasePath();
    auto string = (path + filepath);
    parseFromFile(string, &map, "");
    delete [] path;
    
    auto last_slash_idx = filepath.rfind('/');
    if (last_slash_idx != std::string::npos) directory = filepath.substr(0, last_slash_idx) + "/";
    
    drawTiles();
    
    return true;
}

tiled_map::~tiled_map() {
    mTileLayer.clear();
}


tmxparser::TmxObjectGroup tiled_map::getObjectGroupNamed(std::string name) {
    tmxparser::TmxObjectGroup s;
    for (auto&& layer : map.objectGroupCollection) {
        if (layer.name == name) return layer;
    }
    return s;
}

sprite_ptr tiled_map::getLayerNamed(std::string name) {
    sprite_ptr s = NULL;
    for (auto&& layer : mTileLayer) {
        if (layer.lock()->getName() == name) return layer.lock();
    }
    return s;
}

void tiled_map::drawTiles() {
    if (map.tilesetCollection.size() == 0) return;
    tmxparser::TmxTileset tileset = map.tilesetCollection[0];
    
    SDL_Surface *img = IMG_Load((directory + tileset.image.source).c_str());
    SDL_SetSurfaceBlendMode(img, SDL_BLENDMODE_NONE);
    vec2f imageTileSize = vec2f_make((tileset.tileWidth), (tileset.tileHeight));
    vec2f imageSize = vec2f_make(tileset.image.width, tileset.image.height);
    int tileSpacing = tileset.tileSpacingInImage;
    
    RKTLog("First GID: " << tileset.firstgid);
    RKTLog("Image Source: " << directory + tileset.image.source);
    RKTLog("tile-size: " << imageTileSize.x << " y:" << imageTileSize.y);
    
    for (auto&& tileLayer : map.layerCollection) {
        
        auto surface = SDL_CreateRGBSurface(0,map.width*map.tileWidth,map.height*map.tileHeight,32,img->format->Rmask,img->format->Gmask,img->format->Bmask,amask);

        int index = 0;
        for (int y = 0; y < tileLayer.height; ++y) {
            for (int x = 0; x < tileLayer.width; ++x) {
                
                auto tile = tileLayer.tiles[y*map.width+x];
                
                if (tile.tilesetIndex != -1) {
                    // Draw tile!
                    int numTilesX = ceil(imageSize.x/(imageTileSize.x+tileSpacing));
                    
                    int startGID = tileset.firstgid;
                    int tileGID = tile.gid - startGID;
                    float xpos = (tileGID % numTilesX);
                    float ypos = ((tileGID-xpos) / numTilesX);
                    
                    SDL_Rect sRect;
                    sRect.x = xpos*imageTileSize.x + xpos*tileSpacing;
                    sRect.y = ypos*imageTileSize.y + ypos*tileSpacing;
                    sRect.w = imageTileSize.x;
                    sRect.h = imageTileSize.y;
                    
                    SDL_Rect dRect;
                    dRect.x = x*imageTileSize.x;
                    dRect.y = y*imageTileSize.y;
                    dRect.w = imageTileSize.x;
                    dRect.h = imageTileSize.y;
                    
                    SDL_BlitSurface(img, &sRect, surface, &dRect);
                }
            }
            index++;
        }
        
        auto surSprite = sprite::create(texture::create(surface));
        surSprite->setName(tileLayer.name);
        mTileLayer.push_back(surSprite);
        this->addChild(surSprite);
        SDL_FreeSurface(surface);
    }
    SDL_FreeSurface(img);
}

tmxparser::TmxMap tiled_map::getRawMap() {
    return map;
}

std::vector<sprite_weak_ptr> tiled_map::getAllLayers() {
    return mTileLayer;
}

std::vector<tmxparser::TmxObjectGroup> tiled_map::getAllObjectGroups() {
    return map.objectGroupCollection;
}


const vec2f tiled_map::getSize() {
    return vec2f_make(map.width*map.tileWidth, map.height*map.tileHeight);
}

const vec2f tiled_map::getPosition() {
    return (node::getPosition() - node::getPosition()*getAnchorPoint());
}

RKT_NAMESPACE_END
