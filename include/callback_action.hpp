//
//  callback_action.hpp
//  rawket
//
//  Created by Tom Albrecht on 24.12.15.
//  
//

#ifndef CallbackAction_hpp
#define CallbackAction_hpp

#include "SDL.h"
#include "action.hpp"
#include "node.hpp"

#define CallbackActionLambda(x) [x]
#define CallbackActionCallback std::function<void(void)>

RKT_NAMESPACE_BEGIN

class node;
class callback_action;
typedef std::unique_ptr<callback_action> callback_action_ptr;

/**
 * Calls a callback function after a specified amount of time
 */
class callback_action : public action {
public:
    static callback_action_ptr create(CallbackActionCallback callback);
    
    /**
     * Re-implementation from base class action
     */
    virtual void update();
    
    /**
     * Re-implementation from base class action
     */
    virtual void start();
    
protected:
    bool init(CallbackActionCallback callback);
private:
    CallbackActionCallback mCallback;
};


RKT_NAMESPACE_END
#endif /* CallbackAction_hpp */
