#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "math/Vector2.h"

class OrthographicCamera
{
public:
    OrthographicCamera(float width, float height);

    const glm::mat4& GetViewProjectionMatrix() const;

    void SetPosition(float x, float y);
    Vector2 GetPosition() const;
    void Translate(float x, float y);

    void SetViewportSize(float width, float height);

private:
    Vector2 m_Position;

    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    void RecalculateViewMatrix();
    void RecalculateProjectionMatrix(float width, float height);
};