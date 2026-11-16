#pragma once

#include "glad/glad.h"
#include <vector>
#include <type_traits>

#include "renderer/VertexBufferElement.h"

class VertexBufferLayout
{
public:
    VertexBufferLayout();
    template <typename T>
    void Push(GLsizei count)
    {
        if (std::is_same<T, float>::value)
        {
            VertexBufferElement element;
            element.type = GL_FLOAT;
            element.count = count;
            element.normalized = GL_FALSE;
            m_Stride += element.GetSize();
            m_Elements.push_back(element);
        }
        else if (std::is_same<T, unsigned int>::value)
        {
            VertexBufferElement element;
            element.type = GL_UNSIGNED_INT;
            element.count = count;
            element.normalized = GL_FALSE;
            m_Stride += element.GetSize();
            m_Elements.push_back(element);
        }
        else if (std::is_same<T, unsigned char>::value)
        {
            VertexBufferElement element;
            element.type = GL_UNSIGNED_BYTE;
            element.count = count;
            element.normalized = GL_FALSE;
            m_Stride += element.GetSize();
            m_Elements.push_back(element);
        }
    }
    const std::vector<VertexBufferElement>& GetElements() const;
    GLsizei GetStride() const;


private:
    std::vector<VertexBufferElement> m_Elements;
    GLsizei m_Stride;
};
