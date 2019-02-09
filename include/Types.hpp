//
//  AffineTransform.h
//  rawket
//
//  Created by Tom Albrecht on 09.01.16.
//  
//

#ifndef Types_hpp
#define Types_hpp

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <memory>
#include "SDL.h"

/**
 * Explode a string. Why isn't this in std?
 */
inline const std::vector<std::string> explode(const std::string& s, const char& c) {
    std::string buff;
    std::vector<std::string> v;
    
    for (auto& n : s) {
        if (n != c)
        {
            buff += n;
        }
        else if (n == c && buff != "")
        {
            v.emplace_back(std::move(buff));
            buff.clear();
        }
    }
    if (!buff.empty()) v.push_back(buff);
    
    return v;
}

/**
 * Localization. Available on iOS/macOS
 */
#ifdef __APPLE__
#define RKTLocalizedString(stringDescriptor, alternative) NSLocalizedString
#else
#define RKTLocalizedString(x,x)
#endif


/**
 * Namespace macro, to fix Xcode's annoying auto indentation
 */
#define RKT_NAMESPACE_BEGIN namespace rkt {
#define RKT_NAMESPACE_END }

/**
 * A static create function which calls init on the object.
 * Mainly for the use in scene subclasses
 */
#define RKT_create_FUNC(T) static std::shared_ptr<T> create() { std::shared_ptr<T> n(new T()); n->init(); return n; }

/**
 * Usage: RKT_create__ptr(ClassName) ClassName_ptr;
 */
#define RKT_create_shared__ptr(T) typedef std::shared_ptr<T> T ## _ptr // creates an std::shared_ptr only
#define RKT_create_weak_ptr(T) typedef std::weak_ptr<T> T ## _weak_ptr // creates an std::weak_ptr only
#define RKT_create__ptr(T) RKT_create_shared__ptr(T); RKT_create_weak_ptr(T) // creates an std::weak_ptr AND std::shared_ptr

/**
 * Logging
 */
#define RKTLog(x)  std::cout << "[rawket] " << x << std::endl // Log macro

/**
 * Some deg to rad calculation and vice versa
 */
#define RadiansToDegrees(angleRadians) (angleRadians * 180.0 / 3.1415926535)
#define DegreesToRadians(angleDegrees) (angleDegrees * 3.1415926535 / 180.0)

/**
 * Begin RKT namespace
 */
RKT_NAMESPACE_BEGIN

/**
 * Used for mobile devices' screen orientations.
 */
typedef enum {
    DeviceOrientationPortrait,
    DeviceOrientationUpsideDown,
    DeviceOrientationLandscapeLeft,
    DeviceOrientationLandscapeRight,
} DeviceOrientation;

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
extern bool operator==(const Vec2& lhs, const Vec2& rhs);
extern bool operator!=(const Vec2& lhs, const Vec2& rhs);
extern Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
extern Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
extern Vec2 operator-(const Vec2& rhs);
extern Vec2 operator/(const Vec2& lhs, const Vec2& rhs);
extern Vec2 operator/(const Vec2& lhs, const double& rhs);
extern Vec2 operator*(const Vec2& lhs, const Vec2& rhs);
extern Vec2 operator*(const Vec2& lhs, const float& rhs);




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

extern bool operator==(const Vec3& lhs, const Vec3& rhs);
extern bool operator!=(const Vec3& lhs, const Vec3& rhs);
extern Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
extern Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
extern Vec3 operator-(const Vec3& rhs);
extern Vec3 operator/(const Vec3& lhs, const Vec3& rhs);
extern Vec3 operator/(const Vec3& lhs, const double& rhs);
extern Vec3 operator*(const Vec3& lhs, const Vec3& rhs);
extern Vec3 operator*(const Vec3& lhs, const float& rhs);



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

/**
 * Returns a new Rect with values set to 0.f
 */
extern Rect RectNull();

/**
 * Rect - Vec2 intersection check
 */
extern bool RectIntersectsVec2(Rect r, Vec2 v);

/**
 * Rect - rect intersection check
 */
extern bool RectIntersectsRect(Rect rectA, Rect rectB);

/**
 * Resulting Rect of rect - rect intersection
 */
extern Rect RectIntersection(Rect a, Rect b);

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

extern Rect operator*(const Rect& lhs, const float& rhs);
extern bool operator==(const Rect& lhs, const Rect& rhs);
extern bool operator!=(const Rect& lhs, const Rect& rhs);



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
    KeyCodeUnknown = SDLK_UNKNOWN,
    KeyCodeReturn = SDLK_RETURN,
    KeyCodeEscape = SDLK_ESCAPE,
    KeyCodeBackspace = SDLK_BACKSPACE,
    KeyCodeTab = SDLK_TAB,
    KeyCodeSpace = SDLK_SPACE,
    KeyCodeExclaim = SDLK_EXCLAIM,
    KeyCodeQuotedBL = SDLK_QUOTEDBL,
    KeyCodeHash = SDLK_HASH,
    KeyCodePercent = SDLK_PERCENT,
    KeyCodeDollar = SDLK_DOLLAR,
    KeyCodeAmpersand = SDLK_AMPERSAND,
    KeyCodeQuote = SDLK_QUOTE,
    KeyCodeLeftParenthesis = SDLK_LEFTPAREN,
    KeyCodeParenthesis = SDLK_RIGHTPAREN,
    KeyCodeAsterisk = SDLK_ASTERISK,
    KeyCodePlus = SDLK_PLUS,
    KeyCodeComma = SDLK_COMMA,
    KeyCodeMinus = SDLK_MINUS,
    KeyCodePeriod = SDLK_PERIOD,
    KeyCodeSlash = SDLK_SLASH,
    KeyCode0 = SDLK_0,
    KeyCode1 = SDLK_1,
    KeyCode2 = SDLK_2,
    KeyCode3 = SDLK_3,
    KeyCode4 = SDLK_4,
    KeyCode5 = SDLK_5,
    KeyCode6 = SDLK_6,
    KeyCode7 = SDLK_7,
    KeyCode8 = SDLK_8,
    KeyCode9 = SDLK_9,
    KeyCodeColon = SDLK_COLON,
    KeyCodeSemicolon = SDLK_SEMICOLON,
    KeyCodeLess = SDLK_LESS,
    KeyCodeEquals = SDLK_EQUALS,
    KeyCodeGreater = SDLK_GREATER,
    KeyCodeQuestion = SDLK_QUESTION,
    KeyCodeAt = SDLK_AT,
    
    KeyCodeLeftBracket = SDLK_LEFTBRACKET,
    KeyCodeBackslash = SDLK_BACKSLASH ,
    KeyCodeRightBracket = SDLK_RIGHTBRACKET,
    KeyCodeCaret = SDLK_CARET,
    KeyCodeUnderscore = SDLK_UNDERSCORE,
    KeyCodeBackquote = SDLK_BACKQUOTE,
    KeyCodeA = SDLK_a,
    KeyCodeB = SDLK_b,
    KeyCodeC = SDLK_c,
    KeyCodeD = SDLK_d,
    KeyCodeE = SDLK_e,
    KeyCodeF = SDLK_f,
    KeyCodeG = SDLK_g,
    KeyCodeH = SDLK_h,
    KeyCodeI = SDLK_i,
    KeyCodeJ = SDLK_j,
    KeyCodeK = SDLK_k,
    KeyCodeL = SDLK_l,
    KeyCodeM = SDLK_m,
    KeyCodeN = SDLK_n,
    KeyCodeO = SDLK_o,
    KeyCodeP = SDLK_p,
    KeyCodeQ = SDLK_q,
    KeyCodeR = SDLK_r,
    KeyCodeS = SDLK_s,
    KeyCodeT = SDLK_t,
    KeyCodeU = SDLK_u,
    KeyCodeV = SDLK_v,
    KeyCodeW = SDLK_w,
    KeyCodeX = SDLK_x,
    KeyCodeY = SDLK_y,
    KeyCodeZ = SDLK_z,
    
    KeyCodeCapslock = SDLK_CAPSLOCK,
    
    KeyCodeF1 = SDLK_F1,
    KeyCodeF2 = SDLK_F2,
    KeyCodeF3 = SDLK_F3,
    KeyCodeF4 = SDLK_F4,
    KeyCodeF5 = SDLK_F5,
    KeyCodeF6 = SDLK_F6,
    KeyCodeF7 = SDLK_F7,
    KeyCodeF8 = SDLK_F8,
    KeyCodeF9 = SDLK_F9,
    KeyCodeF10 = SDLK_F10,
    KeyCodeF11 = SDLK_F11,
    KeyCodeF12 = SDLK_F12,
    
    KeyCodePrintscreen = SDLK_PRINTSCREEN,
    KeyCodeScrolllock = SDLK_SCROLLLOCK,
    KeyCodePause = SDLK_PAUSE,
    KeyCodeInsert = SDLK_INSERT,
    KeyCodeHome = SDLK_HOME,
    KeyCodePageUp = SDLK_PAGEUP,
    KeyCodeDelete = SDLK_DELETE,
    KeyCodeEnd = SDLK_END,
    KeyCodePageDown = SDLK_PAGEDOWN,
    KeyCodeRight = SDLK_RIGHT,
    KeyCodeLeft = SDLK_LEFT,
    KeyCodeDown = SDLK_DOWN,
    KeyCodeUp = SDLK_UP,
} KeyCode;


RKT_NAMESPACE_END
#endif /* Types_hpp */
