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

RKT_NAMESPACE_BEGIN

class WaitAction;
RKT_create_shared__ptr(WaitAction);

/**
 * Waits for a specified time
 */
class WaitAction : public Action {
public:
    WaitAction(double dur);
    static WaitAction_ptr create(double duration);
    
    void update();
    void start();
};

    
RKT_NAMESPACE_END
#endif /* WaitAction_hpp */
