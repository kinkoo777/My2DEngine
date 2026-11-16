#include "geometry/Quad.h"

namespace
{
    float vertices[] = {
        // x,     y,      u,    v
        -0.5f, -0.5f,    0.0f, 1.0f,
        0.5f, -0.5f,    1.0f, 1.0f,
        0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f,  0.5f,    0.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
}

Quad::Quad()
    : m_VBO(vertices, sizeof(vertices)),
      m_IBO(indices, sizeof(indices), 6)
{
    VertexBufferLayout layout;

    layout.Push<float>(2); // Position
    layout.Push<float>(2); // UV

    m_VAO.AddBuffer(m_VBO, layout);
}

void Quad::Bind() const
{
    m_VAO.Bind();
    m_IBO.Bind();
}

GLsizei Quad::GetIndexCount() const
{
    return 6;
}