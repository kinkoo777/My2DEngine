#include "renderer/VertexBuffer.h"


VertexBuffer::VertexBuffer(
    const void* data, GLsizeiptr size
)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : m_RendererID(other.m_RendererID)
{
    other.m_RendererID = 0;
}
VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this == &other)
        return *this;

    if (m_RendererID != 0)
        glDeleteBuffers(1, &m_RendererID);

    m_RendererID = other.m_RendererID;
    other.m_RendererID = 0;

    return *this;
}
