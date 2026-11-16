
#pragma once

#include "renderer/Shader.h"
#include "renderer/OrthographicCamera.h"
#include "scene/GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

#include "geometry/Quad.h"

#include <glad/glad.h>

class Renderer
{
public:
    Renderer();

    void Clear();

    void Draw(
        const GameObject &gameObject,
        Shader &shader,
        const OrthographicCamera &camera

    );

    void DrawSprite(
        const Texture &texture,
        const Vector2 &position,
        const Vector2 &size,
        Shader &shader,
        const OrthographicCamera &camera,
        const float rotation);
    void SetBGColor(float x, float y, float z, float a);

private:
    glm::vec4 m_BgColor = glm::vec4(0.1f, 0.1f, 0.15f, 1.0f);
    Quad m_Quad;
};
