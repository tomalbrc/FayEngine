//
//  ThreadManager.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 12.04.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#include "ThreadManager.hpp"

FE_NAMESPACE_BEGIN

static int TestThread(void *ptr) {
    return ((ThreadManager*)ptr)->executeFunction();
}


ThreadManagerPtr ThreadManager::getInstance() {
    static ThreadManagerPtr instance = std::make_shared<ThreadManager>();
    return instance;
}

void ThreadManager::runThread(std::string threadName, std::function<void ()> function) {
    return runThread(threadName, function, false);
}

void ThreadManager::runThread(std::string threadName, std::function<void ()> function, bool waitForThread) {
    m_target = function;
    auto thread = SDL_CreateThread(TestThread, threadName.c_str(), this);
    if (NULL == thread) {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
    } else if (waitForThread) {
        int retVal = 0;
        SDL_WaitThread(thread, &retVal);
        FELog("Thread returned " << retVal);
    }
}

int ThreadManager::executeFunction() {
    this->m_target();
    return 1;
}
    
} // namespace FE

