//
//  ThreadManager.hpp
//  rawket
//
//  Created by Tom Albrecht on 12.04.16.
//  
//

#ifndef ThreadManager_hpp
#define ThreadManager_hpp

#include <stdio.h>
#include "SDL.h"
#include "Types.hpp"

RKT_NAMESPACE_BEGIN

class ThreadManager;
RKT_create__ptr(ThreadManager);

class ThreadManager {
protected:
    std::function<void(void)> m_target;
public:
    static ThreadManager_ptr getInstance();
    
    int executeFunction();
    
    void runThread(std::string threadName, std::function<void(void)> function);
    void runThread(std::string threadName, std::function<void(void)> function, bool waitForThread);
};

RKT_NAMESPACE_END
#endif /* ThreadManager_hpp */
