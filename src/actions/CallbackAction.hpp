//
//  CallbackAction.hpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 24.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef CallbackAction_hpp
#define CallbackAction_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#include "Action.hpp"
#include "Node.hpp"

#define CallbackActionLambda(x) [x]
#define CallbackActionCallback std::function<void(void)>

class Node;
class CallbackAction;
typedef std::unique_ptr<CallbackAction> CallbackActionPtr;

/**
 * Calls a callback function after a specified amount of time
 */
class CallbackAction : public Action {
public:
    static CallbackActionPtr create(CallbackActionCallback callback);
    
    virtual void update();
    virtual void start();
    
protected:
    bool init(CallbackActionCallback callback);
private:
    CallbackActionCallback mCallback;
};


#endif /* CallbackAction_hpp */
