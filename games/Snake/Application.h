
#pragma once

#include "core/Window.h"
#include "scene/Scene.h"

#include "events/Event.h"
#include "input/InputManager.h"

#include "renderer/Shader.h"
#include "renderer/Renderer.h"
#include "renderer/OrthographicCamera.h"

#include "GridMap.h"
#include "GridRenderer.h"

#include <vector>
#include <utility>

class Application
{
public:
    Application();
    ~Application() = default;

    void Run();

private:
    void OnEvent(Event& event);

    void UpdateSnake();
    void UpdateGrid();

private:
    bool m_Running = true;

    Window m_Window;
    InputManager m_Input;

    Shader m_Shader;
    Renderer m_Renderer;

    Scene m_Scene;
    OrthographicCamera m_Camera;

    GridMap m_GridMap;
    GridRenderer m_GridRenderer;

    // Direction
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    // Positions
    std::vector<std::pair<int, int>> apples;
    std::vector<std::pair<int, int>> snakeBody;

    int snakePosX = 5;
    int snakePosY = 5;

    float m_MoveTimer = 0.0f;
    float m_MoveInterval = 0.15f;

    bool m_GrowSnake = false;
};
