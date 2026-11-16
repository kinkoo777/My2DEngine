#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:

    Shader(
        const std::string& vertexPath,
        const std::string& fragmentPath
    );

    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1f(const std::string& name, float value);
    void SetUniform2f(const std::string& name, float valueX, float valueY);
    void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
    void SetUniform1i(const std::string& name, int value);
    void SetUniform3f(const std::string& name, const glm::vec3& value);


private:

    GLuint m_RendererID;

    static std::string ReadFile(const std::string& filepath);

    static GLuint CompileShader(
        GLenum type,
        const std::string& source
    );
};