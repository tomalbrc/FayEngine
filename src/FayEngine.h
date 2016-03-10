//
// FayEngine
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
#define FE_create_Ptr(__TYPE__) std::shared_ptr<__TYPE__>

#include "tmxparser.h"

#include "Window.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"
#include "LabelNode.hpp"
#include "TiledMapNode.hpp"
#include "ButtonNode.hpp"

#include "Texture.hpp"
#include "DrawTexture.hpp"

#include "RemoveFromParent.hpp"
#include "MoveByAction.hpp"
#include "FadeAlphaToAction.hpp"
#include "SpriteAnimationAction.hpp"
#include "SequenceAction.hpp"
#include "WaitAction.hpp"
#include "CallbackAction.hpp"
#include "RotateToAction.hpp"
#include "RotateByAction.hpp"
#include "ScaleToAction.hpp"
#include "RepeatAction.hpp"

#include "AudioEngine.hpp"

#include "NetworkManager.hpp"

#endif /* FayEngine_h */
