
#include "../Renderer.h"


void Renderer::Clear()
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(
    const GameObject& gameObject,
    Shader& shader

)
{
    shader.Bind();

    glm::mat4 model = gameObject.GetTransform().GetMatrix();

    shader.SetUniformMat4("u_Model", model);

    gameObject.GetVertexArray().Bind();
    gameObject.GetIndexBuffer().Bind();


    int count = gameObject.GetIndexBuffer().getCount();

    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}
