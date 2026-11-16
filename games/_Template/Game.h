#pragma once

#include "core/Window.h"
#include "events/Event.h"
#include "input/InputManager.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/OrthographicCamera.h"
#include "scene/Scene.h"
#include "geometry/Quad.h"

#include <memory>

class Game
{
public:
    Game();

    void Run();

private:
    void OnEvent(Event& event);

    void Update(float deltaTime);   // game logic goes here
    void Render();                  // drawing goes here

private:
    bool m_Running = true;

    // Order matters: the Window creates the OpenGL context,
    // so it must be constructed before anything that uses OpenGL.
    Window m_Window;
    InputManager m_Input;

    Shader m_Shader;
    Renderer m_Renderer;
    OrthographicCamera m_Camera;

    Scene m_Scene;
    std::shared_ptr<Quad> m_QuadGeometry;

    // Example player
    float m_PlayerSpeed = 400.0f;   // pixels per second
};
