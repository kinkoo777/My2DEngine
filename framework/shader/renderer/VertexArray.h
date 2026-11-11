#pragma once 
#include "./VertexBuffer.h"
#include <glad/glad.h>
#include "./VertexBufferLayout.h"

class VertexArray
{

public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& vertexBufferLayout);



private:
    GLuint m_RendererID;

};
