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
    
    virtual void keyDown(SDL_KeyboardEvent event);
    virtual void setWindow(Window *window);
    virtual void update();
    
    void animateForImageIndex();
    
    double animationSpeed = 1.0;
    int index = 1;
    SpritePtr sprite = NULL;
    LabelNodePtr infoLabel = NULL;
};

#endif /* MyScene_hpp */
