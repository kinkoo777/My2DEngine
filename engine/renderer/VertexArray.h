
#pragma once

#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include <glad/glad.h>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    // Zakázání kopírování
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    // Povolení přesouvání
    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void AddBuffer(
        const VertexBuffer& vbo,
        const VertexBufferLayout& vertexBufferLayout
    );

private:
    GLuint m_RendererID = 0;
};
