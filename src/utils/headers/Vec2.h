#pragma once

class Vec2 {
public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float scale) const;
    Vec2 operator+=(const Vec2& other);
    Vec2 operator-=(const Vec2& other);
    Vec2 operator*=(float scale);

    float Magnitude() const;
    Vec2 Normalized() const;
    float Angle() const;

    Vec2 Rotated(float angle) const;
    float Distance(const Vec2& other) const;
    
    static float AngleBetween(const Vec2& a, const Vec2& b);
};