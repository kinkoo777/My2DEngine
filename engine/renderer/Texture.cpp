#include "stb_image/stb_image.h"
#include "renderer/Texture.h"
#include <iostream>

Texture::Texture(const std::string &filepath)
{

    if (filepath.empty())
    {
        return;
    }
    unsigned char *data = stbi_load(
        filepath.c_str(),
        &m_Width,
        &m_Height,
        &m_Channels,
        0);

    if (!data)
    {
        std::cout << "Failed to load texture: "
                  << filepath << std::endl;

        std::cout << "STBI error: "
                  << stbi_failure_reason() << std::endl;

        return;
    }

    glGenTextures(1, &m_RendererID);

    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (m_Channels == 3)
    {
        internalFormat = GL_RGB8;
        format = GL_RGB;
    }
    else
    {
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        internalFormat,
        m_Width,
        m_Height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data);

    stbi_image_free(data);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth() const
{
    return m_Width;
}
int Texture::GetHeight() const
{
    return m_Height;
}
GLuint Texture::GetID() const
{
    return m_RendererID;
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}

bool Texture::IsLoaded() const
{
    return m_RendererID != 0;
}