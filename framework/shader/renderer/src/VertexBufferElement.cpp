#include "../VertexBufferElement.h"

GLsizei VertexBufferElement::GetSize() const 
{
    switch (type)
    {
    case GL_FLOAT:
        return sizeof(float) * count;
        break;

    case GL_UNSIGNED_INT:
        return sizeof(unsigned int) * count;
        break;
    
    case GL_UNSIGNED_BYTE: 
        return sizeof(unsigned char) * count;
        break;
    default:
        return 0;
    }

}