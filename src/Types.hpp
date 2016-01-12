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

#define RadiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)
#define DegreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)


/*
 * Color and helper functions
 */

struct Color {
    Uint32 r,g,b,a;
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



/*
 * Vec2
 */

struct Vec2 {
    float x,y;
};
extern Vec2 Vec2Make(float x, float y);
extern Vec2 Vec2Null();

extern bool operator==(Vec2 lhs, const Vec2& rhs);
extern Vec2 operator+(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator-(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator-(const Vec2 rhs);
extern Vec2 operator/(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator/(Vec2 lhs, const double rhs);
extern Vec2 operator*(Vec2 lhs, const Vec2 rhs);
extern Vec2 operator*(Vec2 lhs, const float rhs);



/*
 * Rect
 */

struct Rect {
    Vec2 origin, size;
};
extern Rect RectMake(float x, float y, float w, float h);
extern Rect RectMake(Vec2 origin, Vec2 size);
extern Rect RectNull();

extern bool RectIntersectsVec2(Rect r, Vec2 v);
extern bool RectIntersectsRect(Rect rectA, Rect rectB);




/*
 * Affine transform
 */
struct Matrix {
    float
    m11, m12, m13,
    m21, m22, m23,
    m31, m32, m33;
};
struct AffineTransform {
    Matrix matrix;
    
};
extern AffineTransform AffineTransformIdentity();
extern AffineTransform AffineTransformMakeScale(float x, float y);
extern  AffineTransform AffineTransformMakeTranslate(float x, float y);
extern  AffineTransform AffineTransformMakeRotate(float value);
extern  AffineTransform AffineTransformMultiply(AffineTransform a, AffineTransform b);
extern AffineTransform AffineTransformInverse(AffineTransform transform);

extern Vec2 Vec2ApplyAffineTransform(Vec2 vec, AffineTransform transform);
extern Rect RectApplyAffineTransform(Rect rect, AffineTransform transform);




#endif /* AffineTransform_h */
