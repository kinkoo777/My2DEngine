
#pragma once


#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "scene/GameObject.h"
#include "geometry/Quad.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"

class Scene
{
public:
    Scene();

    void AddGameObject(const std::string& name, std::unique_ptr<GameObject> gameObject);

    GameObject& CreateGameObject(
        const std::string& name,
        std::shared_ptr<Texture> texture = nullptr
    );

    void Render(
        Renderer &renderer,
        Shader &shader,
        const OrthographicCamera &camera) const;

    GameObject &GetGameObject(const std::string& name);

private:
    std::shared_ptr<Quad> m_DefaultQuad;
    std::vector<std::unique_ptr<GameObject>> m_GameObjects;
};
