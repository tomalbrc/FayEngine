//
//  Types.cpp
//  rawket
//
//  Created by Tom Albrecht on 09.01.16.
//  
//

#include "types.hpp"

RKT_NAMESPACE_BEGIN

/**
 * Affine transformations
 */
affine_transform affine_transform_id() {
    affine_transform t;
    t.m11 = 1, t.m12 = 0, t.m13 = 0;
    t.m21 = 0, t.m22 = 1, t.m23 = 0;
    t.m31 = 0, t.m32 = 0, t.m33 = 1;
    return t;
}

affine_transform transform_make_scale(float x, float y) {
    affine_transform t;
    t.m11 = x, t.m12 = 0, t.m13 = 0;
    t.m21 = 0, t.m22 = y, t.m23 = 0;
    t.m31 = 0, t.m32 = 0, t.m33 = 1;
    return t;
}

affine_transform transform_make_translate(float x, float y) {
    affine_transform t;
    t.m11 = 1, t.m12 = 0, t.m13 = x;
    t.m21 = 0, t.m22 = 1, t.m23 = y;
    t.m31 = 0, t.m32 = 0, t.m33 = 1;
    return t;
}

affine_transform transform_make_rot(float value) {
    affine_transform t; // Clockwise rotation matrix
    t.m11 = cosf(value),     t.m12 = sinf(value),     t.m13 = 0;
    t.m21 = -sinf(value),    t.m22 = cosf(value),     t.m23 = 0;
    t.m31 = 0,               t.m32 = 0,               t.m33 = 1;
    return t;
}


affine_transform transform_multiply(affine_transform a, affine_transform b) {
    affine_transform res;
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

 affine_transform transform_inv(affine_transform transform) {
    // computes the inverse of a matrix m
    auto m = transform;
    double det =m.m11 * (m.m22 * m.m33 - m.m32 * m.m23) -
                m.m12 * (m.m21 * m.m33 - m.m23 * m.m31) +
                m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);
    double invdet = 1.0 / det;
    
    affine_transform minv; // inverse of matrix m
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

vec2f vec2f_apply_transform(vec2f vec, affine_transform transform) {
    auto x = vec.x*transform.m11 + vec.y*transform.m12 + transform.m13;
    auto y = vec.x*transform.m21 + vec.y*transform.m22 + transform.m23;
    return vec2f_make(x, y);
}
rectangle rect_apply_transform(rectangle rectangle, affine_transform transform) {
    auto x = rectangle.origin.x*transform.m11 + rectangle.origin.y*transform.m12 + transform.m13;
    auto y = rectangle.origin.x*transform.m21 + rectangle.origin.y*transform.m22 + transform.m23;
    auto p = (rectangle.origin.x+rectangle.size.x)*transform.m11 + (rectangle.origin.y+rectangle.size.y)*transform.m12 + transform.m13;
    auto q = (rectangle.origin.x+rectangle.size.x)*transform.m21 + (rectangle.origin.y+rectangle.size.y)*transform.m22 + transform.m23;
    return rect_make(x, y, p-x, q-y);
}




/**
 * color4u
 */
template <typename T>
color<T> color_make(const T& r, const T& g, const T& b, const T& a = 255) {
    color<T> c;
    c.r = r, c.g = g, c.b = b, c.a = a;
    return c;
}



/**
 * vec2f, vec3f and rectangle
 */
vec2f vec2f_make(float x, float y) {
    vec2f p;
    p.x = x;
    p.y = y;
    return p;
}
vec2f vec2f_make(float xy) {
    vec2f p;
    p.x = xy;
    p.y = xy;
    return p;
}
vec2f vec2f_null() {
    vec2f p;
    p.x = 0.f;
    p.y = 0.f;
    return p;
}
bool operator==(const vec2f& lhs, const vec2f& rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y); }
bool operator!=(const vec2f& lhs, const vec2f& rhs) { return !(lhs == rhs); }
vec2f operator+(const vec2f& lhs, const vec2f& rhs) { return vec2f_make(lhs.x + rhs.x, lhs.y + rhs.y); }
vec2f operator-(const vec2f& lhs, const vec2f& rhs) { return vec2f_make(lhs.x - rhs.x, lhs.y - rhs.y); }
vec2f operator-(const vec2f& rhs) { return vec2f_make(-rhs.x, -rhs.y); }
vec2f operator/(const vec2f& lhs, const vec2f& rhs) { return vec2f_make(lhs.x / rhs.x, lhs.y / rhs.y); }
vec2f operator/(const vec2f& lhs, const double& rhs) { return vec2f_make(lhs.x / rhs, lhs.y / rhs); }
vec2f operator*(const vec2f& lhs, const vec2f& rhs) { return vec2f_make(lhs.x * rhs.x, lhs.y * rhs.y); }
vec2f operator*(const vec2f& lhs, const float& rhs) { return vec2f_make((lhs.x * rhs), (lhs.y * rhs)); }



/**
 * vec3f
 */

vec3f Vec3Make(float x, float y, float z) {
    vec3f p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}
vec3f Vec3Make(float xyz) {
    vec3f p;
    p.x = xyz;
    p.y = xyz;
    p.z = xyz;
    return p;
}
vec3f Vec3Null() {
    vec3f p;
    p.x = 0.f;
    p.y = 0.f;
    p.z = 0.f;
    return p;
}

bool operator==(const vec3f& lhs, const vec3f& rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y); }
bool operator!=(const vec3f& lhs, const vec3f& rhs) { return !(rhs == lhs); }
vec3f operator+(const vec3f& lhs, const vec3f& rhs) { return Vec3Make(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
vec3f operator-(const vec3f& lhs, const vec3f& rhs) { return Vec3Make(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
vec3f operator-(const vec3f& rhs) { return Vec3Make(-rhs.x, -rhs.y, -rhs.z); }
vec3f operator/(const vec3f& lhs, const vec3f& rhs) { return Vec3Make(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }
vec3f operator/(const vec3f& lhs, const double& rhs) { return Vec3Make(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs); }
vec3f operator*(const vec3f& lhs, const vec3f& rhs) { return Vec3Make(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }
vec3f operator*(const vec3f& lhs, const float& rhs) { return Vec3Make((lhs.x * rhs), (lhs.y * rhs), (lhs.z * rhs)); }




/**
 * rectangle
 */

rectangle rect_make(vec2f origin, vec2f size) {
    return rect_make(origin.x, origin.y, size.x, size.y);
}
rectangle rect_make(float x, float y, float w, float h) {
    rectangle p;
    p.origin.x = x;
    p.origin.y = y;
    p.size.x = w;
    p.size.y = h;
    return p;
}
rectangle rect_null() {
    rectangle p;
    p.origin.x = 0.f;
    p.origin.y = 0.f;
    p.size.x = 0.f;
    p.size.y = 0.f;
    return p;
}
bool rect_intersects_vec2f(rectangle r, vec2f v) {
    auto pointX = v.x;
    auto pointY = v.y;
    if (pointX < (r.origin.x + r.size.x) && pointX > r.origin.x &&
        pointY < (r.origin.y + r.size.y) && pointY > r.origin.y)
        return true;
    else
        return false;
}
bool rectangles_intersect(rectangle rectA, rectangle rectB) {
    return (rectA.origin.x < rectB.origin.x + rectB.size.x && rectA.origin.x + rectA.size.x > rectB.origin.x &&
             rectA.origin.y < rectB.origin.y + rectB.size.y && rectA.origin.y + rectA.size.y > rectB.origin.y) ;
}


rectangle rectangle_intersection(rectangle a, rectangle b) { // DOESNT WORK
    rectangle intersection;
    intersection = rect_make(std::max(a.origin.x,b.origin.x), std::max(a.origin.y,b.origin.y),0,0);
    intersection.origin.x = std::min(a.origin.x+a.size.x, b.origin.x+b.size.x) - intersection.origin.x;
    intersection.origin.y = std::min(a.origin.y+a.size.y, b.origin.y+b.size.y) - intersection.origin.y;
    if (intersection.size == vec2f_null())
        return rect_null();
    else
        return intersection;
}


rectangle rect_inset(rectangle r, float inset) {
    return rect_make(r.origin.x+inset/2.0, r.origin.y+inset/2.0, r.size.x-inset, r.size.y-inset);
}

rectangle rect_offset(rectangle r, vec2f offset) {
    return rect_make(r.origin.x+offset.x, r.origin.y+offset.y, r.size.x, r.size.y);
}


rectangle operator*(const rectangle& lhs, const float& rhs) { return rect_make((lhs.origin.x * rhs), (lhs.origin.y * rhs), (lhs.size.x * rhs), (lhs.size.y * rhs)); }
bool operator==(const rectangle& lhs, const rectangle& rhs) { return (lhs.origin == rhs.origin && lhs.size == rhs.size); }
bool operator!=(const rectangle& lhs, const rectangle& rhs) { return !(lhs == rhs); }

RKT_NAMESPACE_END
