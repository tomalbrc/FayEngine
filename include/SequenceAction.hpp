//
//  SequenceAction.hpp
//  rawket
//
//  Created by Tom Albrecht on 22.12.15.
//  
//

#ifndef SequenceAction_hpp
#define SequenceAction_hpp

#include <vector>
#include <iostream>
#include "Action.hpp"
#include "Sprite.hpp"

RKT_NAMESPACE_BEGIN

class SequenceAction;
RKT_create_shared__ptr(SequenceAction);

/**
 * Performs a sequence of actions, one-by-one
 */
class SequenceAction : public Action {
public:
    static SequenceAction_ptr create(std::vector<Action_ptr> actions);
    ~SequenceAction();
    
    void update();
    void start();
    
    
protected:
    bool init(std::vector<Action_ptr> actions);
private:
    std::vector<Action_ptr> mActions;
    int currentIndex = 0;
    void prepareCurrentAction();
};

RKT_NAMESPACE_END
#endif /* SequenceAction_hpp */
