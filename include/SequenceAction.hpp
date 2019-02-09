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

FE_NAMESPACE_BEGIN

class SequenceAction;
FE_create_shared_Ptr(SequenceAction);

/**
 * Performs a sequence of actions, one-by-one
 */
class SequenceAction : public Action {
public:
    static SequenceActionPtr create(std::vector<ActionPtr> actions);
    ~SequenceAction();
    
    void update();
    void start();
    
    
protected:
    bool init(std::vector<ActionPtr> actions);
private:
    std::vector<ActionPtr> mActions;
    int currentIndex = 0;
    void prepareCurrentAction();
};

FE_NAMESPACE_END
#endif /* SequenceAction_hpp */
