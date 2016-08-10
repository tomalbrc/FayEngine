//
//  AffineTransform.h
//  FayEngine
//
//  Created by Tom Albrecht on 09.01.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#ifndef Types_hpp
#define Types_hpp

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "SDL.h"

/**
 * Explode a string. Why isn't this in std?
 */
inline const std::vector<std::string> explode(const std::string& s, const char& c) {
    std::string buff{""};
    std::vector<std::string> v;
    
    for(auto n:s) {
        if(n != c) buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);
    
    return v;
}

/**
 * Localization. Only available on iOS at the moment
 */
#define FELocalizedString(stringDescriptor, alternative) NSLocalizedString


/**
 * Namespace macro, to fix Xcode's annoying auto indentation
 */
#define FE_NAMESPACE_BEGIN namespace FE {
#define FE_NAMESPACE_END }

/**
 * A static create function which calls init on the object.
 * Mainly for the use in Scene subclasses
 */
#define FE_create_FUNC(T) static std::shared_ptr<T> create() { std::shared_ptr<T> n(new T()); n->init(); return n; }

/**
 * Usage: FE_create_Ptr(ClassName) ClassNamePtr;
 */
#define FE_create_shared_Ptr(T) typedef std::shared_ptr<T> T ## Ptr // creates an std::shared_ptr only
#define FE_create_weak_Ptr(T) typedef std::weak_ptr<T> T ## WeakPtr // creates an std::weak_ptr only
#define FE_create_Ptr(T) FE_create_shared_Ptr(T); FE_create_weak_Ptr(T) // creates an std::weak_ptr AND std::shared_ptr

/**
 * Logging
 */
#define FELog(x)  std::cout << "[FayEngine] " << x << std::endl // Log macro

/**
 * Some deg to rad calculation and vice versa
 */
#define RadiansToDegrees(angleRadians) (angleRadians * 180.0 / 3.1415926535)
#define DegreesToRadians(angleDegrees) (angleDegrees * 3.1415926535 / 180.0)

/**
 * Begin FE namespace
 */
FE_NAMESPACE_BEGIN

typedef enum {
    /**
     * Default. No anti-aliasing
     */
    FilteringModeNearest = 0,
    /**
     * Linear scaling. Supported by OpenGL and Direct3D.
     */
    FilteringModeLinear = 1,
    /**
     * Anisotropic scaling. Only supported by Direct3D
     */
    FilteringModeAnisotropic = 2, // Supported by Direct3D
}
/**
 * Filtering modes for the renderer. See EngineHelper setGlobalFilteringMode and getGlobalFilteringMode
 */
FilteringMode;


typedef enum {
    /**
     * No blending
     */
    BlendModeNone = SDL_BLENDMODE_NONE,
    /**
     * Blend alpha
     */
    BlendModeAlpha = SDL_BLENDMODE_BLEND,
    /**
     * Add
     */
    BlendModeAdd = SDL_BLENDMODE_ADD,
    /**
     * Mod (multiply)
     */
    BlendModeMod = SDL_BLENDMODE_MOD,
}
/**
 * Blend modes for Sprites
 */
BlendMode;

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

/**
 * Some Vec2 operator to make your (and my) life easier
 */
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

/**
 * Creates a Vec2 with specified x, y and z values 
 */
extern Vec3 Vec3Make(float x, float y, float z);
/** 
 * Creates a Vec2 with xyz as x, y and z values 
 */
extern Vec3 Vec3Make(float xyz);
/**
 * Creates a Vec2 with x = 0, y = 0, z = 0 
 */
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
    
/**
 * Returns a new Rect with specified x,y,w,h
 */
extern Rect RectMake(float x, float y, float w, float h);
    
/**
 * Returns a new Rect with specified x,y,w,h
 */
extern Rect RectMake(Vec2 origin, Vec2 size);
extern Rect RectNull();

extern bool RectIntersectsVec2(Rect r, Vec2 v);
extern bool RectIntersectsRect(Rect rectA, Rect rectB);

extern Rect RectInset(Rect r, float inset);
extern Rect RectOffset(Rect r, Vec2 offset);

// TODO: do
/*
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
} FEKeyCode;


FE_NAMESPACE_END
#endif /* Types_hpp */
