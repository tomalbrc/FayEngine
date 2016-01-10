//
//  Types.cpp
//  FayEngine
//
//  Created by Tom Albrecht on 09.01.16.
//  Copyright © 2016 Tom Albrecht. All rights reserved.
//

#include "Types.hpp"

/**
 *
 * Affine transformations
 *
 */

extern AffineTransform AffineTransformIdentity() {
    AffineTransform t;
    t.matrix.m11 = 1, t.matrix.m12 = 0, t.matrix.m13 = 0;
    t.matrix.m21 = 0, t.matrix.m22 = 1, t.matrix.m23 = 0;
    t.matrix.m31 = 0, t.matrix.m32 = 0, t.matrix.m33 = 1;
    return t;
}

extern AffineTransform AffineTransformMakeScale(float x, float y) {
    AffineTransform t;
    t.matrix.m11 = x, t.matrix.m12 = 0, t.matrix.m13 = 0;
    t.matrix.m21 = 0, t.matrix.m22 = y, t.matrix.m23 = 0;
    t.matrix.m31 = 0, t.matrix.m32 = 0, t.matrix.m33 = 1;
    return t;
}

extern AffineTransform AffineTransformMakeTranslate(float x, float y) {
    AffineTransform t;
    t.matrix.m11 = 1, t.matrix.m12 = 0, t.matrix.m13 = x;
    t.matrix.m21 = 0, t.matrix.m22 = 1, t.matrix.m23 = y;
    t.matrix.m31 = 0, t.matrix.m32 = 0, t.matrix.m33 = 1;
    return t;
}

extern AffineTransform AffineTransformMakeRotate(float value) {
    AffineTransform t; // Clockwise rotation matrix
    t.matrix.m11 = cosf(value),     t.matrix.m12 = sinf(value),     t.matrix.m13 = 0;
    t.matrix.m21 = -sinf(value),    t.matrix.m22 = cosf(value),     t.matrix.m23 = 0;
    t.matrix.m31 = 0,               t.matrix.m32 = 0,               t.matrix.m33 = 1;
    return t;
}


extern AffineTransform AffineTransformMultiply(AffineTransform a, AffineTransform b) {
    AffineTransform res;
    auto a00 = a.matrix.m11, a01 = a.matrix.m12, a02 = a.matrix.m13;
    auto a10 = a.matrix.m21, a11 = a.matrix.m22, a12 = a.matrix.m23;
    auto a20 = a.matrix.m31, a21 = a.matrix.m32, a22 = a.matrix.m33;
    
    auto b00 = b.matrix.m11, b01 = b.matrix.m12, b02 = b.matrix.m13;
    auto b10 = b.matrix.m21, b11 = b.matrix.m22, b12 = b.matrix.m23;
    auto b20 = b.matrix.m31, b21 = b.matrix.m32, b22 = b.matrix.m33;
    
    res.matrix.m11 = b00 * a00 + b01 * a10 + b02 * a20;
    res.matrix.m12 = b00 * a01 + b01 * a11 + b02 * a21;
    res.matrix.m13 = b00 * a02 + b01 * a12 + b02 * a22;
    
    res.matrix.m21 = b10 * a00 + b11 * a10 + b12 * a20;
    res.matrix.m22 = b10 * a01 + b11 * a11 + b12 * a21;
    res.matrix.m23 = b10 * a02 + b11 * a12 + b12 * a22;
    
    res.matrix.m31 = b20 * a00 + b21 * a10 + b22 * a20;
    res.matrix.m32 = b20 * a01 + b21 * a11 + b22 * a21;
    res.matrix.m33 = b20 * a02 + b21 * a12 + b22 * a22;
    
    return res;
}

extern AffineTransform AffineTransformInverse(AffineTransform transform) {
    // computes the inverse of a matrix m
    auto m = transform.matrix;
    double det =m.m11 * (m.m22 * m.m33 - m.m32 * m.m23) -
                m.m12 * (m.m21 * m.m33 - m.m23 * m.m31) +
                m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);
    double invdet = 1.0 / det;
    
    Matrix minv; // inverse of matrix m
    minv.m11 = (m.m22 * m.m33 - m.m32 * m.m23) * invdet;
    minv.m12 = (m.m13 * m.m32 - m.m12 * m.m33) * invdet;
    minv.m13 = (m.m12 * m.m23 - m.m13 * m.m22) * invdet;
    
    minv.m21 = (m.m23 * m.m31 - m.m21 * m.m33) * invdet;
    minv.m22 = (m.m11 * m.m33 - m.m13 * m.m31) * invdet;
    minv.m23 = (m.m21 * m.m13 - m.m11 * m.m23) * invdet;
    
    minv.m31 = (m.m21 * m.m32 - m.m31 * m.m22) * invdet;
    minv.m32 = (m.m31 * m.m12 - m.m11 * m.m32) * invdet;
    minv.m33 = (m.m11 * m.m22 - m.m21 * m.m12) * invdet;
    
    AffineTransform t;
    t.matrix = minv;
    return t;
}

extern Vec2 Vec2ApplyAffineTransform(Vec2 vec, AffineTransform transform) {
    auto x = vec.x*transform.matrix.m11 + vec.y*transform.matrix.m12 + transform.matrix.m13;
    auto y = vec.x*transform.matrix.m21 + vec.y*transform.matrix.m22 + transform.matrix.m23;
    return Vec2Make(x, y);
}
extern Rect RectApplyAffineTransform(Rect rect, AffineTransform transform) {
    auto x = rect.origin.x*transform.matrix.m11 + rect.origin.y*transform.matrix.m12 + transform.matrix.m13;
    auto y = rect.origin.x*transform.matrix.m21 + rect.origin.y*transform.matrix.m22 + transform.matrix.m23;
    auto p = (rect.origin.x+rect.size.x)*transform.matrix.m11 + (rect.origin.y+rect.size.y)*transform.matrix.m12 + transform.matrix.m13;
    auto q = (rect.origin.x+rect.size.x)*transform.matrix.m21 + (rect.origin.y+rect.size.y)*transform.matrix.m22 + transform.matrix.m23;
    return RectMake(x, y, p-x, q-y);
}




/*
 * Color
 */

extern Color ColorMake(Uint32 r, Uint32 g, Uint32 b, Uint32 a) {
    Color c;
    c.r = r, c.g = g, c.b = b, c.a = a;
    return c;
}
extern Color ColorMake(Uint32 r, Uint32 g, Uint32 b) { return ColorMake(r, g, b, 255); }




/*
 * Rect and Vec2
 */

extern Vec2 Vec2Make(float x, float y) {
    Vec2 p;
    p.x = x;
    p.y = y;
    return p;
}
extern Vec2 Vec2Null() {
    Vec2 p;
    p.x = 0.f;
    p.y = 0.f;
    return p;
}
extern bool operator==(Vec2 lhs, const Vec2& rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y); }
extern Vec2 operator+(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x + rhs.x, lhs.y + rhs.y); }
extern Vec2 operator-(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x - rhs.x, lhs.y - rhs.y); }
extern Vec2 operator-(const Vec2 rhs) { return Vec2Make(-rhs.x, -rhs.y); }
extern Vec2 operator/(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x / rhs.x, lhs.y / rhs.y); }
extern Vec2 operator/(Vec2 lhs, const double rhs) { return Vec2Make(lhs.x / rhs, lhs.y / rhs); }
extern Vec2 operator*(Vec2 lhs, const Vec2 rhs) { return Vec2Make(lhs.x * rhs.x, lhs.y * rhs.y); }
extern Vec2 operator*(Vec2 lhs, const float rhs) { return Vec2Make((lhs.x * rhs), (lhs.y * rhs)); }



extern Rect RectMake(Vec2 origin, Vec2 size) {
    return RectMake(origin.x, origin.y, size.x, size.y);
}
extern Rect RectMake(float x, float y, float w, float h) {
    Rect p;
    p.origin.x = x;
    p.origin.y = y;
    p.size.x = w;
    p.size.y = h;
    return p;
}
extern bool RectIsNull(Rect p) {
    return (bool)(p.origin.x == 0 && p.origin.y == 0 && p.size.x == 0 && p.size.y == 0);
}
extern bool RectIntersectsVec2(Rect r, Vec2 v) {
    double pointX = v.x;
    double pointY = v.y;
    if (pointX < (r.origin.x + r.size.x) && pointX > r.origin.x &&
        pointY < (r.origin.y + r.size.y) && pointY > r.origin.y)
        return true;
    else
        return false;
}
extern bool RectIntersectsRect(Rect rectA, Rect rectB) {
    return !((rectA.origin.x + rectA.size.x) < rectB.origin.x ||
             rectB.origin.x + rectB.size.x < rectA.origin.x ||
             (rectA.origin.y+rectA.size.y) < rectB.origin.y ||
             (rectB.origin.y+rectB.size.y) < rectA.origin.y);
}






