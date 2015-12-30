# FayEngine

FayEngine is a simple, SDL based, 2D Game Engine.
It offers:

- a Scene-Graph 
- actions to ease the struggle of managing animations
- magic

Markdown is a lightweight markup language based on the formatting conventions that people naturally use in email.  As [John Gruber] writes on the [Markdown site][df1]

> The overriding design goal for Markdown's
> formatting syntax is to make it as readable
> as possible. The idea is that a
> Markdown-formatted document should be
> publishable as-is, as plain text, without
> looking like it's been marked up with tags
> or formatting instructions.

This text you see here is *actually* written in Markdown! To get a feel for Markdown's syntax, type some text into the left window and watch the results in the right.

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

