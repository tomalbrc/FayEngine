//
//  MyScene.hpp
//

#ifndef MyScene_hpp
#define MyScene_hpp

#include "FayEngine/FayEngine.h"

class MyScene : public Scene {
public:
    FE_create_FUNC(MyScene);
    bool init();
    virtual void mouseMoved(SDL_MouseMotionEvent, Vec2 coords);
    
    SpritePtr sprite = NULL;
};

#endif /* MyScene_hpp */
