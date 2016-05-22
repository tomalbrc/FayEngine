//
//  NetworkManager.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 10.03.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#include "NetworkManager.hpp"

namespace FE {

NetworkManagerPtr NetworkManager::create() {
    return NetworkManagerPtr(new NetworkManager());
}

std::string NetworkManager::downloadString(std::string url) {
    std::string original = url;
    
    std::string prot = "://";
    size_t s = original.find(prot);
    std::string sub = original.substr(s+prot.length(), original.length());
    
    size_t ccc = sub.find("/", s);
    std::string path = sub.substr(ccc, sub.length()-1);
    
    std::string host = sub.substr(0, ccc);
    
    
    std::cout << "[NetworkManager] Path: " << path  << ", Host: " << host << " ";
    
    
    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, host.c_str(), 80) == -1) {
        FELog("SDLNet_ResolveHost Failed! " << SDLNet_GetError());
        return "";
    }
    
    socket = SDLNet_TCP_Open(&ip);
    if (socket == 0) {
        FELog("SDLNet_TCP_Open Failed! " << SDLNet_GetError());
        return "";
    }
    
    char buffer[1024*2]; // 1 KB * 1024 // 1MB
    std::strcpy(buffer, ("GET "+path+" HTTP/1.1\r\n").c_str());
    std::strcat(buffer, ("Host: "+host+"\r\n").c_str());
    // TODO: 
    std::strcat(buffer, ("Connection: close\r\n")); // this is more of a hack :(
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
    
    // C++ is still a weird but buttiful thing
    
    return myString;
}
    
    
} // namespace FE
