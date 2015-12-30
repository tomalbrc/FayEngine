# FayEngine

FayEngine is a simple, SDL based, 2D Game Engine.
It offers:

- a Scene-Graph 
- actions to ease the struggle of managing animations
- magic

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

### Development

Want to contribute? Great!

### Todos

- Write Tests
- Cleanup Codebase
- More cleanups
- Implement RepeatAction & ColorizeAction
- Implement DrawNode

License
----

MIT


**Free Software, Hell Yeah!**

