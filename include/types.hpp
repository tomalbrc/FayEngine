//
//  affine_transform.h
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
#include <iomanip>
#include <vector>
#include <memory>
#include <sstream>
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
#define RKTLocalizedString(x,y)
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
 * Usage: rkt_create_ptr(ClassName) ClassName_ptr;
 */
#define rkt_create_shared_ptr(T) typedef std::shared_ptr<T> T ## _ptr // creates an std::shared_ptr only
#define rkt_create_weak_ptr(T) typedef std::weak_ptr<T> T ## _weak_ptr // creates an std::weak_ptr only
#define rkt_create_ptr(T) rkt_create_shared_ptr(T); rkt_create_weak_ptr(T) // creates an std::weak_ptr AND std::shared_ptr

/**
 * Logging
 * T needs operator<<
 */
template <class T>
inline void debug_log(const T& t)
{
	auto time_and_date = []() -> std::string
	{
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		std::stringstream ss;
		ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
		return ss.str();
	};
	std::cout << "[rawket " << time_and_date() << "] " << t << std::endl;
}

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
enum DeviceOrientation {
    DeviceOrientationPortrait,
    DeviceOrientationUpsideDown,
    DeviceOrientationLandscapeLeft,
    DeviceOrientationLandscapeRight,
};

/**
 * Filtering modes for the renderer. See engine_helper setGlobalFilteringMode and getGlobalFilteringMode
 */
enum FilteringMode {
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
};

/**
 * Blend modes for Sprites
 */
enum BlendMode {
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
};

/**
 * Color with r g b and a values
 */
template <typename T>
class color {
public:
    /** Red value */
    T r;
    /** Green value */
    T g;
    /** Blue value */
    T b;
    /** Alpha value */
    T a;
};

/**
 * color4<Uint8>
 */
using color4u =  color<unsigned>;

template<typename T>
color<T> color_make(T r, T g, T b, T a = T{1})
{
    return color<T>{r,g,b,a};
}

inline color4u ColorClearColor() { return color_make(0u, 0u, 0u, 0u); }
inline color4u ColorBrownColor() { return color_make(0x99u, 0x66u, 0x33u); }
inline color4u ColorBlackColor() { return color_make(0u, 0u, 0u); }
inline color4u ColorWhiteColor() { return color_make(255u, 255u, 255u); }
inline color4u ColorRedColor() { return color_make(255u, 0u, 0u); }
inline color4u ColorBlueColor() { return color_make(0u, 0u, 255u); }
inline color4u ColorGreenColor() { return color_make(0u, 255u, 0u); }
inline color4u ColorCyanColor() { return color_make(0u, 255u, 255u); } //
inline color4u ColorMagentaColor() { return color_make(255u, 0u, 255u); }
inline color4u ColorYellowColor() { return color_make(255u, 255u, 0u); }
inline color4u ColorPurpleColor() { return color_make(128u, 0u, 128u); }
inline color4u ColorOrangeColor() { return color_make(255u, 165u, 0u); }
inline color4u ColorGrayColor() { return color_make(128u, 128u, 128u); }
inline color4u ColorLightGrayColor() { return color_make(211u, 211u, 211u); }
inline color4u ColorDarkGrayColor() { return color_make(169u, 169u, 169u); }

inline bool operator!=(const color4u& lhs, const color4u& rhs) { return !(lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a); }
inline bool operator==(const color4u& lhs, const color4u& rhs) { return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a); }


/**
 * vec2 with x and y values
 */
template <typename T>
class vec2 {
public:
    /** x value */
    T x;
    /** y value */
    T y;
};

/**
 * vec2f
 */
using vec2f = vec2<float>;

/** Creates a vec2f with specified x and y values */
extern vec2f vec2f_make(float x, float y);
/** Creates a vec2f with xy as x and y values */
extern vec2f vec2f_make(float xy);
/** Creates a vec2f with x = 0 and y */
extern vec2f vec2f_null();

/**
 * Some vec2f operator to make your (and my) life easier
 */
extern bool operator==(const vec2f& lhs, const vec2f& rhs);
extern bool operator!=(const vec2f& lhs, const vec2f& rhs);
extern vec2f operator+(const vec2f& lhs, const vec2f& rhs);
extern vec2f operator-(const vec2f& lhs, const vec2f& rhs);
extern vec2f operator-(const vec2f& rhs);
extern vec2f operator/(const vec2f& lhs, const vec2f& rhs);
extern vec2f operator/(const vec2f& lhs, const double& rhs);
extern vec2f operator*(const vec2f& lhs, const vec2f& rhs);
extern vec2f operator*(const vec2f& lhs, const float& rhs);



/**
 * Vec3 with x, y and z values
 */
template <typename T>
class vec3 {
public:
    /** x value */
    T x;
    /** y value */
    T y;
    /** z value */
    T z;
};


/**
 * vec3f
 */
using vec3f = vec3<float>;

/**
 * Creates a vec2f with specified x, y and z values 
 */
extern vec3f Vec3Make(float x, float y, float z);
/** 
 * Creates a vec2f with xyz as x, y and z values 
 */
extern vec3f Vec3Make(float xyz);
/**
 * Creates a vec2f with x = 0, y = 0, z = 0 
 */
extern vec3f Vec3Null();

extern bool operator==(const vec3f& lhs, const vec3f& rhs);
extern bool operator!=(const vec3f& lhs, const vec3f& rhs);
extern vec3f operator+(const vec3f& lhs, const vec3f& rhs);
extern vec3f operator-(const vec3f& lhs, const vec3f& rhs);
extern vec3f operator-(const vec3f& rhs);
extern vec3f operator/(const vec3f& lhs, const vec3f& rhs);
extern vec3f operator/(const vec3f& lhs, const double& rhs);
extern vec3f operator*(const vec3f& lhs, const vec3f& rhs);
extern vec3f operator*(const vec3f& lhs, const float& rhs);



/**
 * rectangle with origin and size
 */
struct rectangle {
    /** vec2f containing the point of origin */
    vec2f origin;
    /** vec2f cointaing the size */
    vec2f size;
};
    
/**
 * Returns a new rectangle with specified x,y,w,h
 */
extern rectangle rect_make(float x, float y, float w, float h);
    
/**
 * Returns a new rectangle with specified x,y,w,h
 */
extern rectangle rect_make(vec2f origin, vec2f size);

/**
 * Returns a new rectangle with values set to 0.f
 */
extern rectangle rect_null();

/**
 * rectangle - vec2f intersection check
 */
extern bool rect_intersects_vec2f(rectangle r, vec2f v);

/**
 * rectangle - rectangle intersection check
 */
extern bool rectangles_intersect(rectangle rectA, rectangle rectB);

/**
 * Resulting rectangle of rectangle - rectangle intersection
 */
extern rectangle rectangle_intersection(rectangle a, rectangle b);

extern rectangle rect_inset(rectangle r, float inset);
extern rectangle rect_offset(rectangle r, vec2f offset);

// TODO: do
/*
extern rectangle RectGetMinX(rectangle r);
extern rectangle RectGetMidX(rectangle r);
extern rectangle RectGetMaxX(rectangle r);

extern rectangle RectGetMinY(rectangle r);
extern rectangle RectGetMidY(rectangle r);
extern rectangle RectGetMaxY(rectangle r);
*/

extern rectangle operator*(const rectangle& lhs, const float& rhs);
extern bool operator==(const rectangle& lhs, const rectangle& rhs);
extern bool operator!=(const rectangle& lhs, const rectangle& rhs);



/**
 * Affine transform
 */
struct affine_transform {
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
extern affine_transform affine_transform_id();
extern affine_transform transform_make_scale(float x, float y);
extern affine_transform transform_make_translate(float x, float y);
extern affine_transform transform_make_rot(float value);
extern affine_transform transform_multiply(affine_transform a, affine_transform b);
extern affine_transform transform_inv(affine_transform transform);

extern vec2f vec2f_apply_transform(vec2f vec, affine_transform transform);
extern rectangle rect_apply_transform(rectangle rectangle, affine_transform transform);





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
