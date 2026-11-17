
#pragma once


#include <string>
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

    void AddGameObject(const std::string& name,std::unique_ptr<GameObject> gameObject);

    void Render(
        Renderer &renderer,
        Shader &shader,
        const OrthographicCamera &camera) const;

    GameObject &GetGameObject(const std::string& name);

private:
    std::vector<std::unique_ptr<GameObject>> m_GameObjects;
};
