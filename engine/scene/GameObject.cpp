
#include "scene/GameObject.h"

#include <utility>
#include <stdexcept>

GameObject::GameObject(
    std::shared_ptr<Geometry> geometry,
    std::shared_ptr<Texture> texture
)
    : m_Geometry(std::move(geometry)),
      m_Texture(std::move(texture))
{
    if (!m_Geometry)
    {
        throw std::invalid_argument(
            "GameObject requires geometry"
        );
    }
}

GameObject::GameObject(
    std::shared_ptr<Geometry> geometry,
    const std::string& texturePath
)
    : GameObject(
          std::move(geometry),
          texturePath.empty() ? nullptr : std::make_shared<Texture>(texturePath)
      )
{
}

Transform& GameObject::GetTransform()
{
    return m_Transform;
}

const Transform& GameObject::GetTransform() const
{
    return m_Transform;
}

const Geometry& GameObject::GetGeometry() const
{
    return *m_Geometry;
}

const Texture& GameObject::GetTexture() const
{
    return *m_Texture;
}

void GameObject::SetColor(float r, float g, float b)
{
    m_Color = glm::vec3(r, g, b);
}

const glm::vec3& GameObject::GetColor() const
{
    return m_Color;
}

bool GameObject::HasTexture() const
{
    return m_Texture && m_Texture->IsLoaded();
}

const std::string GameObject::GetSceneName()
{
    return m_SceneName;
}

void GameObject::SetSceneName(const std::string& name) 
{
    m_SceneName = name;
}