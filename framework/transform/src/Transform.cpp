
#include "../Transform.h"

Transform::Transform()
    : m_Position(0.0f, 0.0f, 0.0f),
      m_Rotation(0.0f),
      m_Scale(1.0f, 1.0f, 1.0f)
{
}

void Transform::SetPosition(float x, float y, float z)
{
    m_Position = glm::vec3(x, y, z);
}

void Transform::SetRotation(float degrees)
{
    m_Rotation = degrees;
}

void Transform::SetScale(float x, float y, float z)
{
    m_Scale = glm::vec3(x, y, z);
}

glm::mat4 Transform::GetMatrix() const 
{
    glm::mat4 model(1.0f);

    model = glm::translate(model,m_Position);
    model = glm::rotate(model,glm::radians(m_Rotation),glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model,m_Scale);

    return model;
}