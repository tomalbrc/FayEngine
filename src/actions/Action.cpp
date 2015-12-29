//
//  Action.cpp
//  PixelDead_SDL
//
//  Created by Tom Albrecht on 09.12.15.
//  Copyright © 2015 Tom Albrecht. All rights reserved.
//

#include "Action.hpp"
#include "Node.hpp"

bool Action::init(){
    return true;
}
Action::~Action(){
    Logbuch("DESTRUCT Action");
    target = NULL;
};