//
//  AffineTransform.h
//  FayEngine
//
//  Created by Tom Albrecht on 09.01.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef AffineTransform_h
#define AffineTransform_h

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "SDL.h"

/* macros */
#define Logbuch(x)  std::cout << "[LOGBUCHEINTRAG:] " << x << std::endl // Support for older versions
#define FELog(x)  std::cout << "[FayEngine] " << x << std::endl // New Log macro

#define RadiansToDegrees(angleRadians) (angleRadians * 180.0 / 3.1415926535)
#define DegreesToRadians(angleDegrees) (angleDegrees * 3.1415926535 / 180.0)


/**
 * Blend modes for Sprites
 */
typedef enum {
    BlendModeNone,
    BlendModeAlpha,
    BlendModeAdd,
    BlendModeMod, // AKA Multiply?
} BlendMode;

/**
 * Color with r g b and a values
 */
struct Color {
    /** Red value */
    Uint8 r;
    /** Green value */
    Uint8 g;
    /** Blue value */
    Uint8 b;
    /** Alpha value */
    Uint8 a;
};
extern Color ColorMake(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
extern Color ColorMake(Uint8 r, Uint8 g, Uint8 b);
inline Color ColorClearColor() { return ColorMake(0, 0, 0, 0); }
inline Color ColorBrownColor() { return ColorMake(0x99, 0x66, 0x33); }
inline Color ColorBlackColor() { return ColorMake(0, 0, 0); }
inline Color ColorWhiteColor() { return ColorMake(255, 255, 255); }
inline Color ColorRedColor() { return ColorMake(255, 0, 0); }
inline Color ColorBlueColor() { return ColorMake(0, 0, 255); }
inline Color ColorGreenColor() { return ColorMake(0, 255, 0); }
inline Color ColorCyanColor() { return ColorMake(0, 255, 255); } //
inline Color ColorMagentaColor() { return ColorMake(255, 0, 255); }
inline Color ColorYellowColor() { return ColorMake(255, 255, 0); }
inline Color ColorPurpleColor() { return ColorMake(128, 0, 128); }
inline Color ColorOrangeColor() { return ColorMake(255, 165, 0); }
inline Color ColorGrayColor() { return ColorMake(128, 128, 128); }
inline Color ColorLightGrayColor() { return ColorMake(211, 211, 211); }
inline Color ColorDarkGrayColor() { return ColorMake(169, 169, 169); }

inline bool operator!=(const Color& lhs, const Color& rhs) { return !(lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a); }
inline bool operator==(const Color& lhs, const Color& rhs) { return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a); }



/**
 * Vec2 with x and y values
 */
struct Vec2 {
    /** x value */
    float x;
    /** y value */
    float y;
};

/** Creates a Vec2 with specified x and y values */
extern Vec2 Vec2Make(float x, float y);
/** Creates a Vec2 with xy as x and y values */
extern Vec2 Vec2Make(float xy);
/** Creates a Vec2 with x = 0 and y */
extern Vec2 Vec2Null();

extern bool operator==(Vec2 lhs, const Vec2& rhs);
extern Vec2 operator+(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator-(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator-(const Vec2 rhs);
extern Vec2 operator/(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator/(Vec2 lhs, const double rhs);
extern Vec2 operator*(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator*(Vec2 lhs, const float rhs);




/**
 * Vec3 with x, y and z values
 */
struct Vec3 {
    /** x value */
    float x;
    /** y value */
    float y;
    /** z value */
    float z;
};

/** Creates a Vec2 with specified x, y and z values */
extern Vec3 Vec3Make(float x, float y, float z);
/** Creates a Vec2 with xyz as x, y and z values */
extern Vec3 Vec3Make(float xyz);
/** Creates a Vec2 with x = 0, y = 0, z = 0 */
extern Vec3 Vec3Null();




/**
 * Rect with origin and size
 */
struct Rect {
    /** Vec2 containing the point of origin */
    Vec2 origin;
    /** Vec2 cointaing the size */
    Vec2 size;
};
extern Rect RectMake(float x, float y, float w, float h);
extern Rect RectMake(Vec2 origin, Vec2 size);
extern Rect RectNull();

extern bool RectIntersectsVec2(Rect r, Vec2 v);
extern bool RectIntersectsRect(Rect rectA, Rect rectB);

extern Rect RectInset(Rect r, float inset);
extern Rect RectOffset(Rect r, Vec2 offset);

/* TODO
extern Rect RectGetMinX(Rect r);
extern Rect RectGetMidX(Rect r);
extern Rect RectGetMaxX(Rect r);

extern Rect RectGetMinY(Rect r);
extern Rect RectGetMidY(Rect r);
extern Rect RectGetMaxY(Rect r);
*/

extern Rect operator*(Rect lhs, const float rhs);



/**
 * Affine transform
 */
struct AffineTransform {
    /** Value at 0,0 */
    float m11;
    /** Value at 0,1 */
    float m12;
    /** Value at 0,2 */
    float m13;
    /** Value at 1,0 */
    float m21;
    /** Value at 1,1 */
    float m22;
    /** Value at 1,2 */
    float m23;
    /** Value at 2,0 */
    float m31;
    /** Value at 2,1 */
    float m32;
    /** Value at 2,2 */
    float m33;
};
extern AffineTransform AffineTransformIdentity();
extern AffineTransform AffineTransformMakeScale(float x, float y);
extern AffineTransform AffineTransformMakeTranslate(float x, float y);
extern AffineTransform AffineTransformMakeRotate(float value);
extern AffineTransform AffineTransformMultiply(AffineTransform a, AffineTransform b);
extern AffineTransform AffineTransformInverse(AffineTransform transform);

extern Vec2 Vec2ApplyAffineTransform(Vec2 vec, AffineTransform transform);
extern Rect RectApplyAffineTransform(Rect rect, AffineTransform transform);





/**
 * Some helper macros
 */

/**
 * Makes a static create function and calls init on the object
 */
#define FE_create_FUNC(T) static std::shared_ptr<T> create() { std::shared_ptr<T> n(new T()); n->init(); return n; }

/*
 * Usage: FE_create_Ptr(ClassName) ClassNamePtr;
 */
#define FE_create_shared_Ptr(T) typedef std::shared_ptr<T> T ## Ptr
#define FE_create_weak_Ptr(T) typedef std::weak_ptr<T> T ## WeakPtr
#define FE_create_Ptr(T) FE_create_shared_Ptr(T); FE_create_weak_Ptr(T)






/**
 * Keycodes for input handling
 */
typedef enum {
    FEKeyCodeUnknown = SDLK_UNKNOWN,
    FEKeyCodeReturn = SDLK_RETURN,
    FEKeyCodeEscape = SDLK_ESCAPE,
    FEKeyCodeBackspace = SDLK_BACKSPACE,
    FEKeyCodeTab = SDLK_TAB,
    FEKeyCodeSpace = SDLK_SPACE,
    FEKeyCodeExclaim = SDLK_EXCLAIM,
    FEKeyCodeQuotedBL = SDLK_QUOTEDBL,
    FEKeyCodeHash = SDLK_HASH,
    FEKeyCodePercent = SDLK_PERCENT,
    FEKeyCodeDollar = SDLK_DOLLAR,
    FEKeyCodeAmpersand = SDLK_AMPERSAND,
    FEKeyCodeQuote = SDLK_QUOTE,
    FEKeyCodeLeftParenthesis = SDLK_LEFTPAREN,
    FEKeyCodeParenthesis = SDLK_RIGHTPAREN,
    FEKeyCodeAsterisk = SDLK_ASTERISK,
    FEKeyCodePlus = SDLK_PLUS,
    FEKeyCodeComma = SDLK_COMMA,
    FEKeyCodeMinus = SDLK_MINUS,
    FEKeyCodePeriod = SDLK_PERIOD,
    FEKeyCodeSlash = SDLK_SLASH,
    FEKeyCode0 = SDLK_0,
    FEKeyCode1 = SDLK_1,
    FEKeyCode2 = SDLK_2,
    FEKeyCode3 = SDLK_3,
    FEKeyCode4 = SDLK_4,
    FEKeyCode5 = SDLK_5,
    FEKeyCode6 = SDLK_6,
    FEKeyCode7 = SDLK_7,
    FEKeyCode8 = SDLK_8,
    FEKeyCode9 = SDLK_9,
    FEKeyCodeColon = SDLK_COLON,
    FEKeyCodeSemicolon = SDLK_SEMICOLON,
    FEKeyCodeLess = SDLK_LESS,
    FEKeyCodeEquals = SDLK_EQUALS,
    FEKeyCodeGreater = SDLK_GREATER,
    FEKeyCodeQuestion = SDLK_QUESTION,
    FEKeyCodeAt = SDLK_AT,
    
    FEKeyCodeLeftBracket = SDLK_LEFTBRACKET,
    FEKeyCodeBackslash = SDLK_BACKSLASH ,
    FEKeyCodeRightBracket = SDLK_RIGHTBRACKET,
    FEKeyCodeCaret = SDLK_CARET,
    FEKeyCodeUnderscore = SDLK_UNDERSCORE,
    FEKeyCodeBackquote = SDLK_BACKQUOTE,
    FEKeyCodeA = SDLK_a,
    FEKeyCodeB = SDLK_b,
    FEKeyCodeC = SDLK_c,
    FEKeyCodeD = SDLK_d,
    FEKeyCodeE = SDLK_e,
    FEKeyCodeF = SDLK_f,
    FEKeyCodeG = SDLK_g,
    FEKeyCodeH = SDLK_h,
    FEKeyCodeI = SDLK_i,
    FEKeyCodeJ = SDLK_j,
    FEKeyCodeK = SDLK_k,
    FEKeyCodeL = SDLK_l,
    FEKeyCodeM = SDLK_m,
    FEKeyCodeN = SDLK_n,
    FEKeyCodeO = SDLK_o,
    FEKeyCodeP = SDLK_p,
    FEKeyCodeQ = SDLK_q,
    FEKeyCodeR = SDLK_r,
    FEKeyCodeS = SDLK_s,
    FEKeyCodeT = SDLK_t,
    FEKeyCodeU = SDLK_u,
    FEKeyCodeV = SDLK_v,
    FEKeyCodeW = SDLK_w,
    FEKeyCodeX = SDLK_x,
    FEKeyCodeY = SDLK_y,
    FEKeyCodeZ = SDLK_z,
    
    FEKeyCodeCapslock = SDLK_CAPSLOCK,
    
    FEKeyCodeF1 = SDLK_F1,
    FEKeyCodeF2 = SDLK_F2,
    FEKeyCodeF3 = SDLK_F3,
    FEKeyCodeF4 = SDLK_F4,
    FEKeyCodeF5 = SDLK_F5,
    FEKeyCodeF6 = SDLK_F6,
    FEKeyCodeF7 = SDLK_F7,
    FEKeyCodeF8 = SDLK_F8,
    FEKeyCodeF9 = SDLK_F9,
    FEKeyCodeF10 = SDLK_F10,
    FEKeyCodeF11 = SDLK_F11,
    FEKeyCodeF12 = SDLK_F12,
    
    FEKeyCodePrintscreen = SDLK_PRINTSCREEN,
    FEKeyCodeScrolllock = SDLK_SCROLLLOCK,
    FEKeyCodePause = SDLK_PAUSE,
    FEKeyCodeInsert = SDLK_INSERT,
    FEKeyCodeHome = SDLK_HOME,
    FEKeyCodePageUp = SDLK_PAGEUP,
    FEKeyCodeDelete = SDLK_DELETE,
    FEKeyCodeEnd = SDLK_END,
    FEKeyCodePageDown = SDLK_PAGEDOWN,
    FEKeyCodeRight = SDLK_RIGHT,
    FEKeyCodeLeft = SDLK_LEFT,
    FEKeyCodeDown = SDLK_DOWN,
    FEKeyCodeUp = SDLK_UP,
    
    /*
    SDLK_NUMLOCKCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
    SDLK_KP_DIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
    SDLK_KP_MULTIPLY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
    SDLK_KP_MINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
    SDLK_KP_PLUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
    SDLK_KP_ENTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
    SDLK_KP_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
    SDLK_KP_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
    SDLK_KP_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
    SDLK_KP_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
    SDLK_KP_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
    SDLK_KP_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
    SDLK_KP_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
    SDLK_KP_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
    SDLK_KP_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
    SDLK_KP_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
    SDLK_KP_PERIOD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),
    
    SDLK_APPLICATION = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
    SDLK_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
    SDLK_KP_EQUALS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
    SDLK_F13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
    SDLK_F14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
    SDLK_F15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
    SDLK_F16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
    SDLK_F17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
    SDLK_F18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
    SDLK_F19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
    SDLK_F20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
    SDLK_F21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
    SDLK_F22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
    SDLK_F23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
    SDLK_F24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
    SDLK_EXECUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
    SDLK_HELP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
    SDLK_MENU = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
    SDLK_SELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
    SDLK_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
    SDLK_AGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
    SDLK_UNDO = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
    SDLK_CUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
    SDLK_COPY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
    SDLK_PASTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
    SDLK_FIND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
    SDLK_MUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
    SDLK_VOLUMEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
    SDLK_VOLUMEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
    SDLK_KP_COMMA = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
    SDLK_KP_EQUALSAS400 =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),
    
    SDLK_ALTERASE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
    SDLK_SYSREQ = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
    SDLK_CANCEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
    SDLK_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
    SDLK_PRIOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
    SDLK_RETURN2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
    SDLK_SEPARATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
    SDLK_OUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
    SDLK_OPER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
    SDLK_CLEARAGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
    SDLK_CRSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
    SDLK_EXSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),
    
    SDLK_KP_00 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
    SDLK_KP_000 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
    SDLK_THOUSANDSSEPARATOR =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
    SDLK_DECIMALSEPARATOR =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
    SDLK_CURRENCYUNIT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
    SDLK_CURRENCYSUBUNIT =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
    SDLK_KP_LEFTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
    SDLK_KP_RIGHTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
    SDLK_KP_LEFTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
    SDLK_KP_RIGHTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
    SDLK_KP_TAB = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
    SDLK_KP_BACKSPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
    SDLK_KP_A = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
    SDLK_KP_B = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
    SDLK_KP_C = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
    SDLK_KP_D = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
    SDLK_KP_E = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
    SDLK_KP_F = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
    SDLK_KP_XOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
    SDLK_KP_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
    SDLK_KP_PERCENT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
    SDLK_KP_LESS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
    SDLK_KP_GREATER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
    SDLK_KP_AMPERSAND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
    SDLK_KP_DBLAMPERSAND =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
    SDLK_KP_VERTICALBAR =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
    SDLK_KP_DBLVERTICALBAR =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
    SDLK_KP_COLON = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
    SDLK_KP_HASH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
    SDLK_KP_SPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
    SDLK_KP_AT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
    SDLK_KP_EXCLAM = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
    SDLK_KP_MEMSTORE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
    SDLK_KP_MEMRECALL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
    SDLK_KP_MEMCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
    SDLK_KP_MEMADD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
    SDLK_KP_MEMSUBTRACT =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
    SDLK_KP_MEMMULTIPLY =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
    SDLK_KP_MEMDIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
    SDLK_KP_PLUSMINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
    SDLK_KP_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
    SDLK_KP_CLEARENTRY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
    SDLK_KP_BINARY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
    SDLK_KP_OCTAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
    SDLK_KP_DECIMAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
    SDLK_KP_HEXADECIMAL =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),
    
    SDLK_LCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
    SDLK_LSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
    SDLK_LALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
    SDLK_LGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
    SDLK_RCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
    SDLK_RSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
    SDLK_RALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
    SDLK_RGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),
    
    SDLK_MODE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),
    
    SDLK_AUDIONEXT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
    SDLK_AUDIOPREV = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
    SDLK_AUDIOSTOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
    SDLK_AUDIOPLAY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
    SDLK_AUDIOMUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
    SDLK_MEDIASELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
    SDLK_WWW = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
    SDLK_MAIL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
    SDLK_CALCULATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
    SDLK_COMPUTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
    SDLK_AC_SEARCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
    SDLK_AC_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
    SDLK_AC_BACK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
    SDLK_AC_FORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
    SDLK_AC_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
    SDLK_AC_REFRESH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
    SDLK_AC_BOOKMARKS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),
    
    SDLK_BRIGHTNESSDOWN =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
    SDLK_BRIGHTNESSUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
    SDLK_DISPLAYSWITCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
    SDLK_KBDILLUMTOGGLE =
    SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
    SDLK_KBDILLUMDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
    SDLK_KBDILLUMUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
    SDLK_EJECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
    SDLK_SLEEP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP)*/
} FEKeyCode;



#endif /* AffineTransform_h */
