
#include "renderer/Renderer.h"

#include "geometry/Quad.h"

Renderer::Renderer()
    : m_Quad()
{
}

void Renderer::Clear()
{
    glClearColor(m_BgColor.x, m_BgColor.y, m_BgColor.z, m_BgColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetBGColor(float x, float y, float z, float a)
{
    m_BgColor = glm::vec4(x, y, z, a);
}

void Renderer::Draw(
    const GameObject &gameObject,
    Shader &shader,
    const OrthographicCamera &camera)
{
    shader.Bind();

    glm::mat4 model = gameObject.GetTransform().GetMatrix();

    if (gameObject.HasTexture())
    {
        const Texture &texture = gameObject.GetTexture();

        shader.SetUniform1i("u_UseTexture", 1);
        shader.SetUniform1i("u_Texture", 0);
        texture.Bind(0);
    }
    else
    {
        shader.SetUniform1i("u_UseTexture", 0);
    }

    shader.SetUniform3f("u_Color", gameObject.GetColor());

    shader.SetUniformMat4("u_Model", model);

    shader.SetUniformMat4(
        "u_ViewProjection",
        camera.GetViewProjectionMatrix());

    // Bind shared geometry
    gameObject.GetGeometry().Bind();

    glDrawElements(
        GL_TRIANGLES,
        gameObject.GetGeometry().GetIndexCount(),
        GL_UNSIGNED_INT,
        nullptr);
}

void Renderer::DrawSprite(
    const Texture &texture,
    const Vector2 &position,
    const Vector2 &size,
    Shader &shader,
    const OrthographicCamera &camera,
    const float rotation)
{
    shader.Bind();

    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(position.GetX(), position.GetY(), 0.0f));

    model = glm::scale(
        model,
        glm::vec3(size.GetX(), size.GetY(), 1.0f));

    model = glm::rotate(
        model,
        glm::radians(rotation),
        glm::vec3(0.0f, 0.0f, 1.0f));

    shader.SetUniformMat4("u_Model", model);

    shader.SetUniformMat4(
        "u_ViewProjection",
        camera.GetViewProjectionMatrix());

    shader.SetUniform1i("u_UseTexture", 1);
    shader.SetUniform1i("u_Texture", 0);

    shader.SetUniform3f("u_Color", glm::vec3(1.0f));

    texture.Bind(0);

    m_Quad.Bind();

    glDrawElements(
        GL_TRIANGLES,
        m_Quad.GetIndexCount(),
        GL_UNSIGNED_INT,
        nullptr);
}
