//
//  WaitAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
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

    
FE_NAMESPACE_END
#endif /* WaitAction_hpp */
