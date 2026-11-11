#include "../GameObject.h"


GameObject::GameObject(
    const float* vertices,
    size_t vertexSize,
    const unsigned int* indices,
    size_t indexSize,
    GLsizei indexCount
)
    : m_VertexBuffer(vertices, vertexSize),
      m_IndexBuffer(indices, indexSize, indexCount)
{
    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(3);

    m_VertexArray.AddBuffer(m_VertexBuffer, layout);
}


Transform &GameObject::GetTransform()
{
    return m_Transform;
}

const Transform &GameObject::GetTransform() const
{
    return m_Transform;
}

const VertexArray& GameObject::GetVertexArray() const{
    return m_VertexArray;
}


const IndexBuffer& GameObject::GetIndexBuffer() const {
    return m_IndexBuffer;
}