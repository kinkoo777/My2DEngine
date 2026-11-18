
#include "scene/Scene.h"

Scene::Scene()
    : m_DefaultQuad(std::make_shared<Quad>())
{
}

void Scene::AddGameObject(const std::string& name, std::unique_ptr<GameObject> gameObject)
{
    if (gameObject)
    {
        gameObject->SetSceneName(name);
        m_GameObjects.push_back(std::move(gameObject));
    }
}

GameObject& Scene::CreateGameObject(
    const std::string& name,
    std::shared_ptr<Texture> texture)
{
    auto gameObject = std::make_unique<GameObject>(m_DefaultQuad, std::move(texture));
    gameObject->SetSceneName(name);
    m_GameObjects.push_back(std::move(gameObject));

    return *m_GameObjects.back();
}

void Scene::Render(
    Renderer& renderer,
    Shader& shader,
    const OrthographicCamera& camera
) const
{
    for (const auto& gameObject : m_GameObjects)
    {
        if (gameObject)
        {
            renderer.Draw(*gameObject, shader, camera);
        }
    }
}

GameObject& Scene::GetGameObject(const std::string& name)
{
    for (auto& obj : m_GameObjects)
    {
        if (name == obj->GetSceneName())
        {
            return *obj;
        }
    }

    throw std::runtime_error("GameObject with name: " + name + "was not found!");
}

