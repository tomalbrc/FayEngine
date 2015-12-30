//
//  TiledMapNode.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 22.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "TiledMapNode.hpp"

TiledMapNodePtr TiledMapNode::create(const std::string &filepath) {
    TiledMapNodePtr p(new TiledMapNode());
    p->init(filepath);
    return p;
}

bool TiledMapNode::init(const std::string &filepath) {
    map = new tmxparser::TmxMap();
    parseFromFile(filepath.c_str(), map, "");
    
    this->setTexture(Texture::create(Vec2Make(map->width * map->tileWidth,map->height * map->tileHeight), ColorMake(0xFF000000, 0x00FF0000, 0x0000FF00,  0x000000FF)));
    
    drawTiles();
    getObjects();
    
    return true;
}

TiledMapNode::~TiledMapNode() {
    for (auto&& c : getChildren()) {
        FELog("~TiledMapNode CALLED:["<<getName()<<"] Child ref count: "<<c.use_count());
    }
    layers.clear();
}



SpritePtr TiledMapNode::getLayerNamed(std::string name) {
    return layers[name].lock();
}

void TiledMapNode::drawTiles() {
    tmxparser::TmxTileset tileset = map->tilesetCollection[0];
    
    
    SDL_Surface *img = IMG_Load(("res/" + tileset.image.source).c_str());
    Vec2 imageTileSize = Vec2Make((tileset.tileWidth), (tileset.tileHeight));
    Vec2 imageSize = Vec2Make(tileset.image.width, tileset.image.height);
    
    FELog("First GID: " << tileset.firstgid);
    FELog("Image Source: " << tileset.image.source);
    FELog("tile-size: " << imageTileSize.x << " y:" << imageTileSize.y);
    
    
    for (auto&& tileLayer : map->layerCollection) {
        
        SDL_Surface *surface = SDL_CreateRGBSurface(0,map->width*map->tileWidth,map->height*map->tileHeight,24,0xFF000000, 0x00FF0000, 0x0000FF00, tileLayer.name == "ground" ? 0 : 0x000000FF);
        
        int index = 0;
        for (int y = 0; y < tileLayer.height; ++y) {
            for (int x = 0; x < tileLayer.width; ++x) {
                
                tmxparser::TmxLayerTile tile = tileLayer.tiles[y*map->width+x];
                
                if (tile.tilesetIndex != -1) {
                    // Draw tile!
                    int numTilesX = imageSize.x / imageTileSize.x;
                    
                    int startGID = tileset.firstgid;
                    int tileGID = tile.gid - startGID;
                    float xpos = (tileGID % numTilesX);
                    float ypos = ((tileGID-xpos) / numTilesX);
                    
                    SDL_Rect sRect;
                    sRect.x = xpos * imageTileSize.x;
                    sRect.y = ypos * imageTileSize.y;
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
        layers[tileLayer.name] = surSprite;
        this->addChild(surSprite);
        
        SDL_FreeSurface(surface);
    }
    SDL_FreeSurface(img);
}


// TODO: Remove this from the engine and paste into the actual game :P
void TiledMapNode::getObjects() {
    
    // Iterate through all of the object groups.
    for (int i = 0; i < map->objectGroupCollection.size(); ++i) {
        // Get an object group.
        tmxparser::TmxObjectGroup objectGroup = map->objectGroupCollection[i];
        
        // Iterate through all objects in the object group.
        for (int j = 0; j < objectGroup.objects.size(); ++j) {
            tmxparser::TmxObject object = objectGroup.objects[j];
            
            Rect r = RectMake(object.x, object.y, object.width, object.height);
            
            if (objectGroup.name == "walls") {
                walls.push_back(r);
                FELog("Neue wall gesichert!");
            } else if (objectGroup.name == "spawns") {
                mobSpawns.push_back(r);
                FELog("Neuen Spawn gesichert!");
            }
        }
    }
}

tmxparser::TmxMap *TiledMapNode::getRawMap() {
    return map;
}



