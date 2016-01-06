//
// ARBEITEN MIT PROFIS ENGINE
//


#ifndef FayEngine_h
#define FayEngine_h


#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "tinyxml2.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>

#ifdef __linux__
#include <algorithm>
#include <memory>
#endif

/**
 * Makes a static create function and calls init on the object
 */
#define FE_create_FUNC(__TYPE__) static std::shared_ptr<__TYPE__> create() { std::shared_ptr<__TYPE__> n(new __TYPE__()); n->init(); return n; }

#include "tmxparser.h"

#include "Window.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"
#include "LabelNode.hpp"
#include "TiledMapNode.hpp"
#include "ButtonNode.hpp"

#include "RemoveFromParent.hpp"
#include "MoveByAction.hpp"
#include "FadeAlphaToAction.hpp"
#include "SpriteAnimationAction.hpp"
#include "SequenceAction.hpp"
#include "WaitAction.hpp"
#include "CallbackAction.hpp"
#include "RotateAction.hpp"
#include "ScaleToAction.hpp"
#include "RepeatAction.hpp"

#endif /* FayEngine_h */
