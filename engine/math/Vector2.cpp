#include "math/Vector2.h"

Vector2::Vector2(float x, float y)
{
    // Tady nastavíme členské proměnné.
    m_x = x;
    m_y = y;
}

Vector2 Vector2::Normalize() const
{
    float length = Length();

    if (length == 0.0f)
    {
        return Vector2(0.0f, 0.0f);
    }

    return Vector2(m_x / length, m_y / length);
}

float Vector2::Length() const
{
    return std::sqrt(m_x * m_x + m_y * m_y);
}

Vector2 Vector2::operator+(const Vector2 &other) const
{
    return Vector2(
        m_x + other.m_x,
        m_y + other.m_y);
}

Vector2 Vector2::operator-(const Vector2 &other) const
{
    return Vector2(
        m_x - other.m_x,
        m_y - other.m_y);
}

Vector2 Vector2::operator*(float scalar) const
{
    return Vector2(
        m_x * scalar,
        m_y * scalar);
}

bool Vector2::operator==(const Vector2 &other) const
{
    return m_x == other.m_x && m_y == other.m_y;
}

float Vector2::Dot(const Vector2 &other) const
{
    return m_x * other.m_x + m_y * other.m_y;
}

float Vector2::GetX() const
{
    return m_x;
}
float Vector2::GetY() const 
{
    return m_y;
}