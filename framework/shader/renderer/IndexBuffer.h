#pragma once
#include <glad/glad.h>


class IndexBuffer
{
    public: 
        IndexBuffer(const void* data, GLsizeiptr size,unsigned int ind);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        unsigned int getCount()const;

    
    private:
        GLuint m_RendererID;
        unsigned int indices;



};