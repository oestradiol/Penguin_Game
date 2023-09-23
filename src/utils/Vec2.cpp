#include <cmath>
using namespace std;

#include "headers/Vec2.h"

Vec2::Vec2() : x(0.0f), y(0.0f) { }

Vec2::Vec2(float x, float y) : x(x), y(y) { }

Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(float scale) const {
    return Vec2(x * scale, y * scale);
}

float Vec2::Magnitude() const {
    return sqrt(x * x + y * y);
}

Vec2 Vec2::Normalized() const {
    float mag = Magnitude();
    if (mag != 0.0f) {
        return Vec2(x / mag, y / mag);
    }
    return *this;
}

float Vec2::Distance(const Vec2& other) const {
    Vec2 diff = *this - other;
    return diff.Magnitude();
}

float Vec2::Angle() const {
    return atan2(y, x);
}

float Vec2::AngleBetween(const Vec2& a, const Vec2& b) {
    return atan2(b.y - a.y, b.x - a.x);
}

Vec2 Vec2::Rotated(float angle) const {
    float s = sin(angle);
    float c = cos(angle);
    return Vec2(x * c - y * s, x * s + y * c);
}