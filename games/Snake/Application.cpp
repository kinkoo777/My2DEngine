
#include "Application.h"

#include "events/EventDispatcher.h"
#include "events/WindowCloseEvent.h"
#include "events/WindowResizeEvent.h"

#include "input/KeyCodes.h"
#include "core/Time.h"

#include <glad/glad.h>
#include <memory>
#include <iostream>
#include <cstdlib>

// Constructor

Application::Application()
    : m_Window(1280, 720, "My 2D Engine"),
      m_Input(m_Window.GetNativeWindow()),
      m_Shader(
          "assets/shaders/basic.vert",
          "assets/shaders/basic.frag"),
      m_Camera(1280.0f, 720.0f),
      m_GridMap(40, 22),
      m_GridRenderer(32.0f)
{
    m_Window.SetEventCallback(
        [this](Event& event)
        {
            OnEvent(event);
        });

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Load textures

    /*
    auto playerTexture =
        std::make_shared<Texture>("assets/Snake.png");

    auto appleTexture =
        std::make_shared<Texture>("assets/apple.png");

    auto bodyTexture =
        std::make_shared<Texture>("assets/tail.png");
    */


    AssetManger::Load<Texture>("snake", "assets/Snake.png");
    AssetManger::Load<Texture>("apple", "assets/apple.png");
    AssetManger::Load<Texture>("tail", "assets/tail.png");
    

    // Assign textures
    m_GridRenderer.SetTexture(
        TileType::Player, AssetManger::Get<Texture>("snake"));

    m_GridRenderer.SetTexture(
        TileType::Apple, AssetManger::Get<Texture>("apple"));

    m_GridRenderer.SetTexture(
        TileType::SnakeBody, AssetManger::Get<Texture>("tail"));

    // Initial apples
    apples.push_back({10, 8});
    apples.push_back({5, 3});
    apples.push_back({7, 12});

    // Initial direction
    right = true;

    UpdateGrid();
}

// Rebuild grid from game data

void Application::UpdateGrid()
{
    m_GridMap.Clear();

    // Draw apples
    for (const auto& apple : apples)
    {
        m_GridMap.SetTile(
            apple.first,
            apple.second,
            TileType::Apple
        );
    }

    // Draw snake body
    for (const auto& segment : snakeBody)
    {
        m_GridMap.SetTile(
            segment.first,
            segment.second,
            TileType::SnakeBody
        );
    }

    // Draw snake head last
    m_GridMap.SetTile(
        snakePosX,
        snakePosY,
        TileType::Player
    );
}

// Update snake

void Application::UpdateSnake()
{
    // Save old head position
    int oldX = snakePosX;
    int oldY = snakePosY;

    // Move head
    if (up)
        snakePosY--;

    else if (down)
        snakePosY++;

    else if (left)
        snakePosX--;

    else if (right)
        snakePosX++;

    // Wrap around X
    if (snakePosX >= m_GridMap.GetWidth())
        snakePosX = 0;

    if (snakePosX < 0)
        snakePosX = m_GridMap.GetWidth() - 1;

    // Wrap around Y
    if (snakePosY >= m_GridMap.GetHeight())
        snakePosY = 0;

    if (snakePosY < 0)
        snakePosY = m_GridMap.GetHeight() - 1;

    // Check apple collision
    for (auto it = apples.begin(); it != apples.end();)
    {
        if (snakePosX == it->first &&
            snakePosY == it->second)
        {
            std::cout << "Apple collected!" << std::endl;

            m_GrowSnake = true;

            it = apples.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Move body
    if (!snakeBody.empty())
    {
        // Save previous body positions
        for (size_t i = snakeBody.size() - 1; i > 0; i--)
        {
            snakeBody[i] = snakeBody[i - 1];
        }

        // First segment follows old head
        snakeBody[0] = {oldX, oldY};
    }

    // Grow snake
    if (m_GrowSnake)
    {
        snakeBody.push_back({oldX, oldY});
        m_GrowSnake = false;
    }

    UpdateGrid();
}

// Main game loop

void Application::Run()
{
    while (m_Running && !m_Window.ShouldClose())
    {
        m_Window.Update();

        Time::Update();
        m_Input.Update();

        float deltaTime = Time::GetDeltaTime();

        m_MoveTimer += deltaTime;

        // Input
        if (m_Input.IsKeyJustPressed(Key::W) && !down)
        {
            up = true;
            down = false;
            left = false;
            right = false;

            m_GridRenderer.SetRotation(0.0f);
        }

        if (m_Input.IsKeyJustPressed(Key::S) && !up)
        {
            up = false;
            down = true;
            left = false;
            right = false;

            m_GridRenderer.SetRotation(-180.0f);
        }

        if (m_Input.IsKeyJustPressed(Key::A) && !right)
        {
            up = false;
            down = false;
            left = true;
            right = false;

            m_GridRenderer.SetRotation(-90.0f);
        }

        if (m_Input.IsKeyJustPressed(Key::D) && !left)
        {
            up = false;
            down = false;
            left = false;
            right = true;

            m_GridRenderer.SetRotation(90.0f);
        }

        // Movement timer
        if (m_MoveTimer >= m_MoveInterval)
        {
            m_MoveTimer -= m_MoveInterval;

            UpdateSnake();
        }

        // Render
        m_Renderer.Clear();

        m_GridRenderer.Render(
            m_GridMap,
            m_Renderer,
            m_Shader,
            m_Camera
        );

        m_Window.SwapBuffers();
    }
}

// Event handling

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<WindowCloseEvent>(
        [this](WindowCloseEvent& e)
        {
            m_Running = false;
        });

    dispatcher.Dispatch<WindowResizeEvent>(
        [this](WindowResizeEvent& e)
        {
            m_Camera.SetViewportSize(
                static_cast<float>(e.GetWidth()),
                static_cast<float>(e.GetHeight())
            );
        });
}
