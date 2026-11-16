#pragma once 

#include <glad/glad.h>

struct VertexBufferElement
{
    GLenum type;
    GLuint count;
    GLboolean normalized;

    GLsizei GetSize() const;

};
