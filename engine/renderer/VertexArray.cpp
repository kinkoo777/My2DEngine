
#include "renderer/VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
    if (m_RendererID != 0)
        glDeleteVertexArrays(1, &m_RendererID);
}

VertexArray::VertexArray(VertexArray&& other) noexcept
    : m_RendererID(other.m_RendererID)
{
    other.m_RendererID = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
    if (this == &other)
        return *this;

    if (m_RendererID != 0)
        glDeleteVertexArrays(1, &m_RendererID);

    m_RendererID = other.m_RendererID;
    other.m_RendererID = 0;

    return *this;
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(
    const VertexBuffer& vbo,
    const VertexBufferLayout& vertexBufferLayout
)
{
    const auto& elements = vertexBufferLayout.GetElements();
    size_t offset = 0;

    vbo.Bind();

    for (size_t i = 0; i < elements.size(); i++)
    {
        glVertexAttribPointer(
            i,
            elements[i].count,
            elements[i].type,
            elements[i].normalized,
            vertexBufferLayout.GetStride(),
            reinterpret_cast<const void*>(offset)
        );

        offset += elements[i].GetSize();

        glEnableVertexAttribArray(i);
    }
}
