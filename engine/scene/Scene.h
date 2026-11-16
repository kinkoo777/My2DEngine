
#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "scene/GameObject.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"

class Scene
{
public:
    Scene();

    void AddGameObject(std::unique_ptr<GameObject> gameObject);

    void Render(
        Renderer &renderer,
        Shader &shader,
        const OrthographicCamera &camera) const;

    GameObject &GetGameObject(size_t index);

private:
    std::vector<std::unique_ptr<GameObject>> m_GameObjects;
};
