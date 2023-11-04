#pragma once

#include "Vec2.h"

class Rect {
public:
    float x;
    float y;
    float w;
    float h;

    Rect();
    Rect(float x, float y, float w, float h);

    Rect operator+(const Vec2& vec) const;
    Rect operator-(const Vec2& vec) const;
    Rect operator+=(const Vec2& vec);
    Rect operator-=(const Vec2& vec);

    void SetCenter(Vec2 newCenter);
    Vec2 Center() const;
    
    float Distance(const Rect& other) const;
    bool Contains(const Vec2& point) const;
};