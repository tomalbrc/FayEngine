//
//  RepeatAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 29.12.15.
//  
//

#ifndef RepeatAction_hpp
#define RepeatAction_hpp

#include "Action.hpp"
#include "Sprite.hpp"

RKT_NAMESPACE_BEGIN

class Node;
class RepeatAction;
typedef std::unique_ptr<RepeatAction> RepeatAction_ptr;

/**
 * Repeats an action x times
 * If times equals 0 the target Action runs forever
 */
class RepeatAction : public Action {
public:
    RepeatAction(Action_ptr action, int times);
    static RepeatAction_ptr create(Action_ptr action, int times); // 0 to run forever
    virtual ~RepeatAction();
    
    void update();
    void start();
private:
    bool mForever;
    int mRepeatTimes = 1;
    Action_ptr mTargetAction = NULL;
};

    
RKT_NAMESPACE_END
#endif /* RepeatAction_hpp */

