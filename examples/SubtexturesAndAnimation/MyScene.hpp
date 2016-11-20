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
    
    virtual void keyDown(FE::FEKeyCode key);
    virtual void setWindow(FE::WindowPtr window);
    virtual void update();
    
    void animateForImageIndex();
    
    double animationSpeed = 1.0;
    int index = 1;
    FE::SpritePtr sprite = NULL;
    FE::LabelNodePtr infoLabel = NULL;
};

#endif /* MyScene_hpp */
