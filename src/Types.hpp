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
#include "SDL.h"

/* macros */
#define Logbuch(x)  std::cout << "[LOGBUCHEINTRAG:] " << x << std::endl // Support for older versions
#define FELog(x)  std::cout << "[FayEngine] " << x << std::endl // New Log macro

#define RadiansToDegrees(angleRadians) (angleRadians * 180.0 / 3.1415926535)
#define DegreesToRadians(angleDegrees) (angleDegrees * 3.1415926535 / 180.0)


/**
 * Color with r g b and a values
 */
struct Color {
    /** Red value */
    Uint32 r;
    /** Green value */
    Uint32 g;
    /** Blue value */
    Uint32 b;
    /** Alpha value */
    Uint32 a;
};
extern Color ColorMake(Uint32 r, Uint32 g, Uint32 b, Uint32 a);
extern Color ColorMake(Uint32 r, Uint32 g, Uint32 b);
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




#endif /* AffineTransform_h */
