
#pragma once

#include <memory>
#include <string>

#include "scene/Transform.h"
#include "geometry/Geometry.h"
#include "assetmanager/Assets.h"


class GameObject
{
public:
    GameObject(
        std::shared_ptr<Geometry> geometry,
        std::shared_ptr<Texture> texture = nullptr
    );

    GameObject(
        std::shared_ptr<Geometry> geometry,
        const std::string& texturePath
    );

    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;

    GameObject(GameObject&&) = delete;
    GameObject& operator=(GameObject&&) = delete;

    Transform& GetTransform();
    const Transform& GetTransform() const;

    const Geometry& GetGeometry() const;

    const Texture& GetTexture() const;

    void SetColor(float r, float g, float b);
    const glm::vec3& GetColor() const;

    bool HasTexture() const;

    const std::string GetSceneName();
    void SetSceneName(const std::string& name);

private:
    Transform m_Transform;

    std::shared_ptr<Geometry> m_Geometry;

    std::shared_ptr<Texture> m_Texture;
    std::string m_SceneName;
    glm::vec3 m_Color = glm::vec3(1.0f);
};
