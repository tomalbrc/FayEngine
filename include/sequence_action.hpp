//
//  sequence_action.hpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#ifndef SequenceAction_hpp
#define SequenceAction_hpp

#include <vector>
#include <iostream>
#include "action.hpp"
#include "sprite.hpp"

RKT_NAMESPACE_BEGIN

class sequence_action;
RKT_create_shared__ptr(sequence_action);

/**
 * Performs a sequence of actions, one-by-one
 */
class sequence_action : public action {
public:
    static sequence_action_ptr create(std::vector<action_ptr> actions);
    ~sequence_action();
    
    void update();
    void start();
    
    
protected:
    bool init(std::vector<action_ptr> actions);
private:
    std::vector<action_ptr> mActions;
    int currentIndex = 0;
    void prepareCurrentAction();
};

RKT_NAMESPACE_END
#endif /* SequenceAction_hpp */
