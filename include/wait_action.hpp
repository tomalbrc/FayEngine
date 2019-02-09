//
//  wait
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#ifndef WaitAction_hpp
#define WaitAction_hpp

#include <vector>
#include <iostream>
#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class wait_action;
RKT_create_shared__ptr(wait_action);

/**
 * Waits for a specified time
 */
class wait_action : public action {
public:
    wait_action(double dur);
    static wait_action_ptr create(double duration);
    
    void update();
    void start();
};

    
RKT_NAMESPACE_END
#endif /* WaitAction_hpp */
