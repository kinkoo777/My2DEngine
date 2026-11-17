
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
        const std::string& texturePath = ""
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

private:
    Transform m_Transform;

    std::shared_ptr<Geometry> m_Geometry;

    Texture m_Texture;

    glm::vec3 m_Color = glm::vec3(1.0f);
};
