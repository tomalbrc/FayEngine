//
//  CallbackAction.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 24.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#ifndef CallbackAction_hpp
#define CallbackAction_hpp

#include "SDL.h"
#include "Action.hpp"
#include "Node.hpp"

#define CallbackActionLambda(x) [x]
#define CallbackActionCallback std::function<void(void)>

FE_NAMESPACE_BEGIN

class Node;
class CallbackAction;
typedef std::unique_ptr<CallbackAction> CallbackActionPtr;

/**
 * Calls a callback function after a specified amount of time
 */
class CallbackAction : public Action {
public:
    static CallbackActionPtr create(CallbackActionCallback callback);
    
    /**
     * Re-implementation from base class Action
     */
    virtual void update();
    
    /**
     * Re-implementation from base class Action
     */
    virtual void start();
    
protected:
    bool init(CallbackActionCallback callback);
private:
    CallbackActionCallback mCallback;
};


} // namespace FE
#endif /* CallbackAction_hpp */
