# FayEngine

FayEngine is a simple, SDL based, 2D Game Engine.
It offers:

- a Scene-Graph 
- actions to ease the struggle of managing animations
- magic

The main reason I did this was to improve my C++ and my knowledge about Game Engines and probably use it in production one sunny day. 

This Engine is not considered to be stable at the moment.

### Version
0.1

### Support

The Engine uses a number of open source projects. 
Following dependecies need to be installed in order to compile:
- libsdl2-dev
- libsdl2-image-dev
- libsdl2-ttf-dev
- libtinyxml-dev

### Installation

You need at least g++ 4.7 and SDL2 2.0.3

```sh
$ make <PLATFORM> && sudo make install
```

Copies ./lib/libFayEngine.a to /usr/local/lib 
And ./incude/* to /usr/local/include/FayEngine 


### Code Example

Every object has shared ownership (std::shared_ptr<>). Every Class has a typedef with 'Ptr' suffix

In your main.cpp's main():
```cpp
int main() {
    EngineHelper::getInstance()->Init(); // Inits SDL and it's library extensions
    EngineHelper::getInstance()->setEnableVSync(true);    
    
    auto win = Window::create("My Window Title", Vec2Make(640,480));
    auto scene = Scene::create();
    win->presentScene(scene);
    win->startLoop();
    
    return 0;
}
```

Adding a Node to the Scene or other nodes:
```cpp
auto node = Node::create();
scne->addChild();
```

Loading and displaying an image in scene with and position of x=100 y=100:
```cpp
auto node = Sprite::create("res/image.png"); // Load with filename (std::string)
node->setPosition(Vec2Make(100,100)); // Vec2 is a struct with two float vars called x and y
scne->addChild();
```

Rotating a Sprite by 180° within 1 second:
```cpp
auto node = Sprite::create("res/image.png"); // Load with filename (std::string)
node->runAction(RotateAction::create(1.0, 180)); // (duration, degrees)
scne->addChild();
```

Also See CallbackAction, FadeAlphaToAction, MoveByAction, RemoveFromParent, RotateAction, SequenceAction ...



The Texture object's create facroty method passes a shared pointer to the EngineHelper singleton class' textureCache in order to reduce redudant loading of resources:
```cpp
// Removes every texture whichs only reference is in the textureCache, thus Unused
EngineHelper::getInstance()->removeUnusedTexture();
EngineHelper::getInstance()->removeTextureFromCache(TexturePtr texture); // Removes given texture from cache, will get reloaded if needed
```

The EngineHelper also holds a reference to the SDL_Renderer
```cpp
EngineHelper::getInstance()->getRenderer();
```

### Development

Want to contribute? Great!

### Todos

- Cleanup Codebase
- More cleanups
- Comment Code better 
- Write Tests
- Implement RepeatAction & ColorizeAction
- Implement DrawNode

License
----

MIT


**Free Software, Hell Yeah!**

