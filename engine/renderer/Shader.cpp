#include "renderer/Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>

std::string Shader::ReadFile(const std::string &filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Failed to open shader file: " + filepath);
    }

    std::stringstream stream;
    stream << file.rdbuf();

    return stream.str();
}

GLuint Shader::CompileShader(
    GLenum type,
    const std::string &source)
{
    GLuint shader = glCreateShader(type);

    const char *sourceCode = source.c_str();

    glShaderSource(
        shader,
        1,
        &sourceCode,
        nullptr);

    glCompileShader(shader);

    GLint success;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success);

    if (!success)
    {
        GLint length = 0;

        glGetShaderiv(
            shader,
            GL_INFO_LOG_LENGTH,
            &length);

        std::vector<char> infoLog(length);

        glGetShaderInfoLog(
            shader,
            length,
            nullptr,
            infoLog.data());

        std::cerr << "Shader compilation error:\n";
        std::cerr << infoLog.data() << std::endl;

        glDeleteShader(shader);

        throw std::runtime_error("Shader compilation failed!");
    }

    return shader;
}

Shader::Shader(
    const std::string &vertexPath,
    const std::string &fragmentPath)
{
    std::string vertexSource = ReadFile(vertexPath);
    std::string fragmentSource = ReadFile(fragmentPath);

    GLuint vertexShader = CompileShader(
        GL_VERTEX_SHADER,
        vertexSource);

    GLuint fragmentShader = 0;

    try
    {
        fragmentShader = CompileShader(
            GL_FRAGMENT_SHADER,
            fragmentSource);

        m_RendererID = glCreateProgram();

        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);

        glLinkProgram(m_RendererID);

        GLint success;

        glGetProgramiv(
            m_RendererID,
            GL_LINK_STATUS,
            &success);

        if (!success)
        {
            GLint length = 0;

            glGetProgramiv(
                m_RendererID,
                GL_INFO_LOG_LENGTH,
                &length);

            std::vector<char> infoLog(length);

            glGetProgramInfoLog(
                m_RendererID,
                length,
                nullptr,
                infoLog.data());

            std::cerr << "Shader linking error:\n";
            std::cerr << infoLog.data() << std::endl;

            throw std::runtime_error("Shader linking failed!");
        }

        glDetachShader(m_RendererID, vertexShader);
        glDetachShader(m_RendererID, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    catch (...)
    {
        glDeleteShader(vertexShader);

        if (fragmentShader != 0)
            glDeleteShader(fragmentShader);

        if (m_RendererID != 0)
        {
            glDeleteProgram(m_RendererID);
            m_RendererID = 0;
        }

        throw;
    }
}

void Shader::SetUniform1f(const std::string &name, float value)
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
    {
        std::cerr << "Uniform not found: " << name << std::endl;
        return;
    }
    glUniform1f(location, value);
}

void Shader::SetUniform1i(const std::string& name, int value) 
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
    {
        std::cerr << "Uniform not found: " << name << std::endl;
        return;
    }
    glUniform1i(location, value);
}

void Shader::SetUniform2f(const std::string& name, float valueX, float valueY) 
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());


    if (location == -1) {
        std::cerr << "Uniform not found " << name << std::endl;
        return;
    }


    glUniform2f(location, valueX, valueY);
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& value) 
{
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
    {
        std::cerr << "Uniform not found: " << name << std::endl;
        return;
    }
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());

    if (location == -1) {
        std::cerr << "Uniform not found " << name << std::endl;
        return;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}