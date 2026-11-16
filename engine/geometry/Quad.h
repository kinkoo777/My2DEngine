#pragma once

#include "geometry/Geometry.h"

#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexBufferLayout.h"

class Quad : public Geometry
{
public:
    Quad();

    void Bind() const override;
    GLsizei GetIndexCount() const override;

private:
    VertexBuffer m_VBO;
    IndexBuffer m_IBO;
    VertexArray m_VAO;
};