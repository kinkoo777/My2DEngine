#pragma once

#include <glad/glad.h>
#include "../transform/Transform.h"
#include "../shader/renderer/VertexArray.h"
#include "../shader/renderer/VertexBuffer.h"
#include "../shader/renderer/IndexBuffer.h"
#include "../shader/renderer/VertexBufferLayout.h"
#include "../shader/Shader.h"

class GameObject
{
public:
    GameObject(
    const float* vertices,
    size_t vertexSize,
    const unsigned int* indices,
    size_t indexSize,
    GLsizei indexCount);

    Transform &GetTransform();
    const Transform &GetTransform() const;
    const VertexArray& GetVertexArray() const;
    const IndexBuffer& GetIndexBuffer() const;
    

private:
    Transform m_Transform;
    VertexArray m_VertexArray;;
    IndexBuffer m_IndexBuffer;
    VertexBuffer  m_VertexBuffer;
};