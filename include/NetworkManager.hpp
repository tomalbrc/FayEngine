//
//  NetworkManager.hpp
//  rawket
//
//  Created by Tom Albrecht on 10.03.16.
//  
//

#ifndef NetworkManager_hpp
#define NetworkManager_hpp

#include <stdio.h>
#include <string>
#include <cstring>
#include <map>
#include "SDL_net.h"
#include "Types.hpp"

RKT_NAMESPACE_BEGIN

typedef enum HTTPRequestType_t:int {
    GetRequest,
    PostRequest,
} HTTPRequestType;

class NetworkManager;
RKT_create__ptr(NetworkManager);

class NetworkManager {
    TCPsocket socket;
public:
    static NetworkManager_ptr create();
    ~NetworkManager();
    
    std::string downloadString(HTTPRequestType requestType, std::map<std::string, std::string> headers, std::string url);
};

RKT_NAMESPACE_END
#endif /* NetworkManager_hpp */
