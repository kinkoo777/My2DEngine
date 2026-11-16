#include "renderer/IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, GLsizeiptr size,unsigned int ind)
{
    indices = ind;
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
    if (m_RendererID != 0)
        glDeleteBuffers(1, &m_RendererID);
}
unsigned int IndexBuffer::getCount() const
{
    return indices;
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    : m_RendererID(other.m_RendererID),
      indices(other.indices)
{
    other.m_RendererID = 0;
    other.indices = 0;
}


IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    if (this == &other)
        return *this;

    if (m_RendererID != 0)
        glDeleteBuffers(1, &m_RendererID);

    m_RendererID = other.m_RendererID;
    indices = other.indices;

    other.m_RendererID = 0;
    other.indices = 0;

    return *this;
}