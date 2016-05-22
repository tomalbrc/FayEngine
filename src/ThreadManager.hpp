//
//  ThreadManager.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 12.04.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef ThreadManager_hpp
#define ThreadManager_hpp

#include <stdio.h>
#include "SDL.h"
#include "Types.hpp"

namespace FE {

class ThreadManager;
FE_create_Ptr(ThreadManager);

class ThreadManager {
protected:
    std::function<void(void)> m_target;
public:
    static ThreadManagerPtr getInstance();
    
    int executeFunction();
    
    void runThread(std::string threadName, std::function<void(void)> function);
    void runThread(std::string threadName, std::function<void(void)> function, bool waitForThread);
};

} // namespace FE
#endif /* ThreadManager_hpp */
