#pragma once

#include <string>
#include <iostream>
#include <glad/glad.h> // nebo GLEW/GLFW - podle toho, co používáš na OpenGL
#include "stb_image/stb_image.h"

class Texture
{
public:
    Texture() = default;

    explicit Texture(const std::string &filepath)
    {
        if (!filepath.empty())
        {
            LoadFromFile(filepath);
        }
    }

    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    // 1. DŮLEŽITÉ: Destruktor, aby se textura smazala z grafické karty, když zanikne shared_ptr!
    ~Texture()
    {
        if (m_RendererID != 0)
        {
            glDeleteTextures(1, &m_RendererID);
        }
    }

    bool LoadFromFile(const std::string &filepath)
    {
        std::cout << "Loading texture from: " << filepath << "\n";

        if (filepath.empty())
        {
            return false; // 2. OPRAVA: Funkce vrací bool, prázdné "return;" by nešlo zkompilovat
        }

        // 3. TIP PRO OPENGL: Obrázky na disku jsou uložené shora dolů, ale OpenGL je čte zdola nahoru.
        // Bez tohoto řádku bys měl ve hře všechny textury vzhůru nohama:
        stbi_set_flip_vertically_on_load(1);

        unsigned char *data = stbi_load(
            filepath.c_str(),
            &m_Width,
            &m_Height,
            &m_Channels,
            0);

        if (!data)
        {
            std::cout << "Failed to load texture: " << filepath << "\n";
            std::cout << "STBI error: " << stbi_failure_reason() << "\n";
            return false; // 2. OPRAVA: Tady také musí být return false;
        }

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Volitelné: Nastavení opakování/ořezu textury na okrajích
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        GLenum internalFormat = 0;
        GLenum format = 0;

        if (m_Channels == 4) // 4. OPRAVA: Je bezpečnější kontrolovat přímo 4 kanály (RGBA) a 3 (RGB)
        {
            internalFormat = GL_RGBA8;
            format = GL_RGBA;
        }
        else if (m_Channels == 3)
        {
            internalFormat = GL_RGB8;
            format = GL_RGB;
        }
        else
        {
            std::cout << "Nepodporovany pocet kanalu (" << m_Channels << ") u textury: " << filepath << "\n";
            stbi_image_free(data);
            return false;
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

        glBindTexture(GL_TEXTURE_2D, 0); // Odvázání textury (dobrý zvyk v OpenGL)
        stbi_image_free(data);

        return true;
    }

    // Metody pro použití textury při vykreslování
    void Bind(unsigned int slot = 0) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    GLuint GetID() const { return m_RendererID; }
    bool IsLoaded() const { return m_RendererID != 0; }

private:
    int m_Width = 0;
    int m_Height = 0;
    int m_Channels = 0;

    GLuint m_RendererID = 0;
};