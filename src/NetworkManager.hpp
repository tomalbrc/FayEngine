//
//  NetworkManager.hpp
//  FayEngine
//
//  Created by Tom Albrecht on 10.03.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef NetworkManager_hpp
#define NetworkManager_hpp

#include <stdio.h>
#include "SDL_net.h"
#include <string>
#include "Types.hpp"

class NetworkManager;
FE_create_Ptr(NetworkManager);

class NetworkManager {
    TCPsocket socket;
public:
    static NetworkManagerPtr create();
    
    std::string downloadString(std::string url);
};

#endif /* NetworkManager_hpp */
