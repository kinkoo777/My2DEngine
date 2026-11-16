#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, GLsizeiptr size);
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;

    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_RendererID;
};