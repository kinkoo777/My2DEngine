#include "renderer/OrthographicCamera.h"


OrthographicCamera::OrthographicCamera(float width, float height)
    : m_Position(0.0f, 0.0f)
{
    RecalculateProjectionMatrix(width, height);
    RecalculateViewMatrix();
}

const glm::mat4& OrthographicCamera::GetViewProjectionMatrix() const
{
    return m_ViewProjectionMatrix;
}

void OrthographicCamera::SetPosition(float x, float y)
{
    m_Position = Vector2(x, y);

    RecalculateViewMatrix();
}

Vector2 OrthographicCamera::GetPosition() const
{
    return m_Position;
}

void OrthographicCamera::Translate(float x, float y)
{
    m_Position = m_Position + Vector2(x, y);

    RecalculateViewMatrix();
}

void OrthographicCamera::SetViewportSize(float width, float height)
{
    if (width <= 0.0f || height <= 0.0f)
        return;

    RecalculateProjectionMatrix(width, height);
}

void OrthographicCamera::RecalculateProjectionMatrix(float width, float height)
{
    m_ProjectionMatrix = glm::ortho(
        0.0f,
        width,
        height,
        0.0f,
        -1.0f,
        1.0f
    );

    m_ViewProjectionMatrix =
        m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    m_ViewMatrix = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(
            -m_Position.GetX(),
            -m_Position.GetY(),
            0.0f
        )
    );

    m_ViewProjectionMatrix =
        m_ProjectionMatrix * m_ViewMatrix;
}