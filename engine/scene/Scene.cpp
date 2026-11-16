
#include "scene/Scene.h"

Scene::Scene()
{
}

void Scene::AddGameObject(std::unique_ptr<GameObject> gameObject)
{
    if (gameObject)
        m_GameObjects.push_back(std::move(gameObject));
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

GameObject& Scene::GetGameObject(size_t index)
{
    return *m_GameObjects.at(index);
}

