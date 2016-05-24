//
//  Types.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 09.01.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#include "Types.hpp"

FE_NAMESPACE_BEGIN

/**
 * Affine transformations
 */
AffineTransform AffineTransformIdentity() {
    AffineTransform t;
    t.m11 = 1, t.m12 = 0, t.m13 = 0;
    t.m21 = 0, t.m22 = 1, t.m23 = 0;
    t.m31 = 0, t.m32 = 0, t.m33 = 1;
    return t;
}

AffineTransform AffineTransformMakeScale(float x, float y) {
    AffineTransform t;
    t.m11 = x, t.m12 = 0, t.m13 = 0;
    t.m21 = 0, t.m22 = y, t.m23 = 0;
    t.m31 = 0, t.m32 = 0, t.m33 = 1;
    return t;
}

AffineTransform AffineTransformMakeTranslate(float x, float y) {
    AffineTransform t;
    t.m11 = 1, t.m12 = 0, t.m13 = x;
    t.m21 = 0, t.m22 = 1, t.m23 = y;
    t.m31 = 0, t.m32 = 0, t.m33 = 1;
    return t;
}

AffineTransform AffineTransformMakeRotate(float value) {
    AffineTransform t; // Clockwise rotation matrix
    t.m11 = cosf(value),     t.m12 = sinf(value),     t.m13 = 0;
    t.m21 = -sinf(value),    t.m22 = cosf(value),     t.m23 = 0;
    t.m31 = 0,               t.m32 = 0,               t.m33 = 1;
    return t;
}


AffineTransform AffineTransformMultiply(AffineTransform a, AffineTransform b) {
    AffineTransform res;
    auto a00 = a.m11, a01 = a.m12, a02 = a.m13;
    auto a10 = a.m21, a11 = a.m22, a12 = a.m23;
    auto a20 = a.m31, a21 = a.m32, a22 = a.m33;
    
    auto b00 = b.m11, b01 = b.m12, b02 = b.m13;
    auto b10 = b.m21, b11 = b.m22, b12 = b.m23;
    auto b20 = b.m31, b21 = b.m32, b22 = b.m33;
    
    res.m11 = b00 * a00 + b01 * a10 + b02 * a20;
    res.m12 = b00 * a01 + b01 * a11 + b02 * a21;
    res.m13 = b00 * a02 + b01 * a12 + b02 * a22;
    
    res.m21 = b10 * a00 + b11 * a10 + b12 * a20;
    res.m22 = b10 * a01 + b11 * a11 + b12 * a21;
    res.m23 = b10 * a02 + b11 * a12 + b12 * a22;
    
    res.m31 = b20 * a00 + b21 * a10 + b22 * a20;
    res.m32 = b20 * a01 + b21 * a11 + b22 * a21;
    res.m33 = b20 * a02 + b21 * a12 + b22 * a22;
    
    return res;
}

 AffineTransform AffineTransformInverse(AffineTransform transform) {
    // computes the inverse of a matrix m
    auto m = transform;
    double det =m.m11 * (m.m22 * m.m33 - m.m32 * m.m23) -
                m.m12 * (m.m21 * m.m33 - m.m23 * m.m31) +
                m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);
    double invdet = 1.0 / det;
    
    AffineTransform minv; // inverse of matrix m
    minv.m11 = (m.m22 * m.m33 - m.m32 * m.m23) * invdet;
    minv.m12 = (m.m13 * m.m32 - m.m12 * m.m33) * invdet;
    minv.m13 = (m.m12 * m.m23 - m.m13 * m.m22) * invdet;
    
    minv.m21 = (m.m23 * m.m31 - m.m21 * m.m33) * invdet;
    minv.m22 = (m.m11 * m.m33 - m.m13 * m.m31) * invdet;
    minv.m23 = (m.m21 * m.m13 - m.m11 * m.m23) * invdet;
    
    minv.m31 = (m.m21 * m.m32 - m.m31 * m.m22) * invdet;
    minv.m32 = (m.m31 * m.m12 - m.m11 * m.m32) * invdet;
    minv.m33 = (m.m11 * m.m22 - m.m21 * m.m12) * invdet;
    
    return minv;
}

Vec2 Vec2ApplyAffineTransform(Vec2 vec, AffineTransform transform) {
    auto x = vec.x*transform.m11 + vec.y*transform.m12 + transform.m13;
    auto y = vec.x*transform.m21 + vec.y*transform.m22 + transform.m23;
    return Vec2Make(x, y);
}
Rect RectApplyAffineTransform(Rect rect, AffineTransform transform) {
    auto x = rect.origin.x*transform.m11 + rect.origin.y*transform.m12 + transform.m13;
    auto y = rect.origin.x*transform.m21 + rect.origin.y*transform.m22 + transform.m23;
    auto p = (rect.origin.x+rect.size.x)*transform.m11 + (rect.origin.y+rect.size.y)*transform.m12 + transform.m13;
    auto q = (rect.origin.x+rect.size.x)*transform.m21 + (rect.origin.y+rect.size.y)*transform.m22 + transform.m23;
    return RectMake(x, y, p-x, q-y);
}




/*
 * Color
 */
Color ColorMake(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    Color c;
    c.r = r, c.g = g, c.b = b, c.a = a;
    return c;
}
Color ColorMake(Uint8 r, Uint8 g, Uint8 b) { return ColorMake(r, g, b, 255); }




/*
 * Vec2, Vec3 and Rect
 */
Vec2 Vec2Make(float x, float y) {
    Vec2 p;
    p.x = x;
    p.y = y;
    return p;
}
Vec2 Vec2Make(float xy) {
    Vec2 p;
    p.x = xy;
    p.y = xy;
    return p;
}
Vec2 Vec2Null() {
    Vec2 p;
    p.x = 0.f;
    p.y = 0.f;
    return p;
}
bool operator==(Vec2 lhs, const Vec2& rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y); }
Vec2 operator+(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x + rhs.x, lhs.y + rhs.y); }
Vec2 operator-(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x - rhs.x, lhs.y - rhs.y); }
Vec2 operator-(const Vec2 rhs) { return Vec2Make(-rhs.x, -rhs.y); }
Vec2 operator/(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x / rhs.x, lhs.y / rhs.y); }
Vec2 operator/(Vec2 lhs, const double rhs) { return Vec2Make(lhs.x / rhs, lhs.y / rhs); }
Vec2 operator*(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x * rhs.x, lhs.y * rhs.y); }
Vec2 operator*(Vec2 lhs, const float rhs) { return Vec2Make((lhs.x * rhs), (lhs.y * rhs)); }



Vec3 Vec3Make(float x, float y, float z) {
    Vec3 p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}
Vec3 Vec3Make(float xyz) {
    Vec3 p;
    p.x = xyz;
    p.y = xyz;
    p.z = xyz;
    return p;
}
Vec3 Vec3Null() {
    Vec3 p;
    p.x = 0.f;
    p.y = 0.f;
    p.z = 0.f;
    return p;
}


Rect RectMake(Vec2 origin, Vec2 size) {
    return RectMake(origin.x, origin.y, size.x, size.y);
}
Rect RectMake(float x, float y, float w, float h) {
    Rect p;
    p.origin.x = x;
    p.origin.y = y;
    p.size.x = w;
    p.size.y = h;
    return p;
}
bool RectIsNull(Rect p) {
    return (bool)(p.origin.x == 0 && p.origin.y == 0 && p.size.x == 0 && p.size.y == 0);
}
bool RectIntersectsVec2(Rect r, Vec2 v) {
    auto pointX = v.x;
    auto pointY = v.y;
    if (pointX < (r.origin.x + r.size.x) && pointX > r.origin.x &&
        pointY < (r.origin.y + r.size.y) && pointY > r.origin.y)
        return true;
    else
        return false;
}
bool RectIntersectsRect(Rect rectA, Rect rectB) {
    return (rectA.origin.x < rectB.origin.x + rectB.size.x && rectA.origin.x + rectA.size.x > rectB.origin.x &&
             rectA.origin.y < rectB.origin.y + rectB.size.y && rectA.origin.y + rectA.size.y > rectB.origin.y) ;
}

Rect RectInset(Rect r, float inset) {
    return RectMake(r.origin.x+inset/2.0, r.origin.y+inset/2.0, r.size.x-inset, r.size.y-inset);
}

Rect RectOffset(Rect r, Vec2 offset) {
    return RectMake(r.origin.x+offset.x, r.origin.y+offset.y, r.size.x, r.size.y);
}



Rect operator*(Rect lhs, const float rhs) { return RectMake((lhs.origin.x * rhs), (lhs.origin.y * rhs), (lhs.size.x * rhs), (lhs.size.y * rhs)); }



} // namespace FE