
#pragma once
#include <glad/glad.h>

class IndexBuffer
{
public:
    IndexBuffer(const void* data, GLsizeiptr size, unsigned int ind);
    ~IndexBuffer();

    // Zakázání kopírování
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    // Povolení přesouvání
    IndexBuffer(IndexBuffer&& other) noexcept;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    unsigned int getCount() const;

private:
    GLuint m_RendererID = 0;
    unsigned int indices = 0;
};
