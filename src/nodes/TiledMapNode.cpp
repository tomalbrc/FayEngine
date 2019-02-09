//
//  TiledMapNode.cpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#include "TiledMapNode.hpp"

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

TiledMapNode_ptr TiledMapNode::create(const std::string &filepath) {
    TiledMapNode_ptr p(new TiledMapNode());
    p->init(filepath);
    return p;
}

bool TiledMapNode::init(const std::string &filepath) {
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

TiledMapNode::~TiledMapNode() {
    mTileLayer.clear();
}


tmxparser::TmxObjectGroup TiledMapNode::getObjectGroupNamed(std::string name) {
    tmxparser::TmxObjectGroup s;
    for (auto&& layer : map.objectGroupCollection) {
        if (layer.name == name) return layer;
    }
    return s;
}

Sprite_ptr TiledMapNode::getLayerNamed(std::string name) {
    Sprite_ptr s = NULL;
    for (auto&& layer : mTileLayer) {
        if (layer.lock()->getName() == name) return layer.lock();
    }
    return s;
}

void TiledMapNode::drawTiles() {
    if (map.tilesetCollection.size() == 0) return;
    tmxparser::TmxTileset tileset = map.tilesetCollection[0];
    
    SDL_Surface *img = IMG_Load((directory + tileset.image.source).c_str());
    SDL_SetSurfaceBlendMode(img, SDL_BLENDMODE_NONE);
    Vec2 imageTileSize = Vec2Make((tileset.tileWidth), (tileset.tileHeight));
    Vec2 imageSize = Vec2Make(tileset.image.width, tileset.image.height);
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
        
        auto surSprite = Sprite::create(Texture::create(surface));
        surSprite->setName(tileLayer.name);
        mTileLayer.push_back(surSprite);
        this->addChild(surSprite);
        SDL_FreeSurface(surface);
    }
    SDL_FreeSurface(img);
}

tmxparser::TmxMap TiledMapNode::getRawMap() {
    return map;
}

std::vector<Sprite_weak_ptr> TiledMapNode::getAllLayers() {
    return mTileLayer;
}

std::vector<tmxparser::TmxObjectGroup> TiledMapNode::getAllObjectGroups() {
    return map.objectGroupCollection;
}


const Vec2 TiledMapNode::getSize() {
    return Vec2Make(map.width*map.tileWidth, map.height*map.tileHeight);
}

const Vec2 TiledMapNode::getPosition() {
    return (Node::getPosition() - Node::getPosition()*getAnchorPoint());
}

RKT_NAMESPACE_END
