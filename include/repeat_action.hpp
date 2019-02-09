//
//  repeat_action.hpp
//  rawket
//
//  Created by Tom Albrecht on 29.12.15.
//  
//

#ifndef RepeatAction_hpp
#define RepeatAction_hpp

#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class node;
class repeat_action;
typedef std::unique_ptr<repeat_action> repeat_action_ptr;

/**
 * Repeats an action x times
 * If times equals 0 the target action runs forever
 */
class repeat_action : public action {
public:
    repeat_action(action_ptr action, int times);
    static repeat_action_ptr create(action_ptr action, int times); // 0 to run forever
    virtual ~repeat_action();
    
    void update();
    void start();
private:
    bool mForever;
    int mRepeatTimes = 1;
    action_ptr mTargetAction = NULL;
};

    
RKT_NAMESPACE_END
#endif /* RepeatAction_hpp */

