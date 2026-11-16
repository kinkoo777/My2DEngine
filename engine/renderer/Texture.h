
#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    int GetWidth() const;
    int GetHeight() const;
    GLuint GetID() const;

    bool IsLoaded() const;

private:
    int m_Width = 0;
    int m_Height = 0;
    int m_Channels = 0;

    GLuint m_RendererID = 0;

    GLenum internalFormat = 0;
    GLenum format = 0;
};
