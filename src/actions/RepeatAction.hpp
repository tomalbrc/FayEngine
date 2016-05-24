//
//  RepeatAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 29.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef RepeatAction_hpp
#define RepeatAction_hpp

#include "Action.hpp"
#include "Sprite.hpp"

FE_NAMESPACE_BEGIN

class Node;
class RepeatAction;
typedef std::unique_ptr<RepeatAction> RepeatActionPtr;

/**
 * Repeats an action x times
 * If times equals 0 the target Action runs forever
 */
class RepeatAction : public Action {
public:
    RepeatAction(ActionPtr action, int times);
    static RepeatActionPtr create(ActionPtr action, int times); // 0 to run forever
    virtual ~RepeatAction();
    
    void update();
    void start();
private:
    bool mForever;
    int mRepeatTimes = 1;
    ActionPtr mTargetAction = NULL;
};

    
FE_NAMESPACE_END
#endif /* RepeatAction_hpp */

