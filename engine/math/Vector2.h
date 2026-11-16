
#pragma once

#include <cmath>

class Vector2
{
public:
    Vector2(float x, float y);

    float Length() const;
    Vector2 Normalize() const;

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;

    bool operator==(const Vector2& other) const;

    float Dot(const Vector2& other) const;

    float GetX() const;
    float GetY() const;

private:
    float m_x;
    float m_y;
};
