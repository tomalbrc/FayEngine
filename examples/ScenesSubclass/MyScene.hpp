//
//  MyScene.hpp
//

#ifndef MyScene_hpp
#define MyScene_hpp

#include "FayEngine/FayEngine.h"

class MyScene : public FE::Scene {
public:
    FE_create_FUNC(MyScene);
    bool init();
    virtual void mouseMoved(SDL_MouseMotionEvent, FE::Vec2 coords);
    
    FE::SpritePtr sprite = NULL;
};

#endif /* MyScene_hpp */
