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
#include <string>
#include <cstring>
#include <map>
#include "SDL_net.h"
#include "Types.hpp"

FE_NAMESPACE_BEGIN

typedef enum HTTPRequestType_t:int {
    GetRequest,
    PostRequest,
} HTTPRequestType;

class NetworkManager;
FE_create_Ptr(NetworkManager);

class NetworkManager {
    TCPsocket socket;
public:
    static NetworkManagerPtr create();
    ~NetworkManager();
    
    std::string downloadString(HTTPRequestType requestType, std::map<std::string, std::string> headers, std::string url);
};

FE_NAMESPACE_END
#endif /* NetworkManager_hpp */
