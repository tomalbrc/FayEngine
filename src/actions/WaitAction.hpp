//
//  WaitAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 22.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef WaitAction_hpp
#define WaitAction_hpp

#include <vector>
#include <iostream>
#include "Action.hpp"
#include "Sprite.hpp"

FE_NAMESPACE_BEGIN

class WaitAction;
FE_create_shared_Ptr(WaitAction);

/**
 * Waits for a specified time
 */
class WaitAction : public Action {
public:
    WaitAction(double dur);
    static WaitActionPtr create(double duration);
    
    void update();
    void start();
};

    
} // namespace FE
#endif /* WaitAction_hpp */
