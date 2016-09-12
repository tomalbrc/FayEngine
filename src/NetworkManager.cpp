//
//  NetworkManager.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 10.03.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#include "NetworkManager.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
// THERES POSSIBLE LEAK
FE_NAMESPACE_BEGIN

NetworkManager::~NetworkManager() {
    
}

NetworkManagerPtr NetworkManager::create() {
    return NetworkManagerPtr(new NetworkManager());
}

std::string NetworkManager::downloadString(HTTPRequestType requestType, std::map<std::string, std::string> headers, std::string url) {
    std::string original = url;
    
    std::string prot = "://";
    size_t s = original.find(prot);
    std::string sub = original.substr(s+prot.length(), original.length());
    
    size_t ccc = sub.find("/", s);
    std::string path = sub.substr(ccc, sub.length()-1);
    
    std::string host = sub.substr(0, ccc);
    
    auto secure = original.substr(0, s) == "https";
    
    FELog(secure);
    
    
    std::cout << "[NetworkManager] Path: " << path  << ", Host: " << host << " ";
    
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, (host).c_str(), secure?443:80) == -1) {
        FELog("SDLNet_ResolveHost Failed! " << SDLNet_GetError());
        FELog("SDLNet_ResolveHost Failed! " << SDLNet_GetError());
        return "";
    }
    
    socket = SDLNet_TCP_Open(&ip);
    if (socket == 0) {
        FELog("SDLNet_TCP_Open Failed! " << SDLNet_GetError());
        return "";
    }
    
    char buffer[1024*2]; // 1 KB * 1024 // 1MB
    std::strcpy(buffer, ((requestType == HTTPRequestType::GetRequest ? std::string("GET") : std::string("POST"))+" "+path+" HTTP/1.1\r\n").c_str());
    
    headers.insert({"Host",""+host});
    headers.insert({"Connection","close"});
    for (auto&& header: headers) {
        std::strcat(buffer, (header.first+": "+header.second+"\r\n").c_str());
    }
    
    std::strcat(buffer, "\r\n");
    
    std::string myString = "";
    
    SDLNet_TCP_Send(socket, &buffer, (int)strlen(buffer));
    memset(&buffer[0], 0, sizeof(buffer));
    while (SDLNet_TCP_Recv(socket, &buffer, 2)) {
        std::string ddd(buffer);
        if (ddd.length() == 0) break;
        myString += ddd;
        memset(&buffer[0], 0, sizeof(buffer));
    }
    
    return myString;
}


FE_NAMESPACE_END
