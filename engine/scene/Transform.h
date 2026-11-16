
#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "math/Vector2.h"

class Transform
{
public:
    Transform();

    void SetPosition(float x, float y);
    void SetRotation(float degrees);
    void SetScale(float x, float y);
    void Translate(float x, float y);

    const Vector2& GetPosition() const;
    
    
    glm::mat4 GetMatrix() const;

private:
    Vector2 m_Position;
    float m_Rotation;
    Vector2 m_Scale;
};
