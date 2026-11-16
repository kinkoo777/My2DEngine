
#include "scene/Transform.h"

Transform::Transform()
    : m_Position(0.0f, 0.0f),
      m_Rotation(0.0f),
      m_Scale(1.0f, 1.0f)
{
}

void Transform::SetPosition(float x, float y)
{
    m_Position = Vector2(x, y);
}

void Transform::SetRotation(float degrees)
{
    m_Rotation = degrees;
}

void Transform::SetScale(float x, float y)
{
    m_Scale = Vector2(x, y);
}

glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 model(1.0f);

    model = glm::translate(model, glm::vec3(m_Position.GetX(), m_Position.GetY(), 0.0f));
    model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(
        model,
        glm::vec3(m_Scale.GetX(), m_Scale.GetY(), 1.0f));

    return model;
}

void Transform::Translate(float x, float y) 
{
    m_Position = m_Position + Vector2(x,y);
}

const Vector2& Transform::GetPosition() const
{
    return m_Position;
}