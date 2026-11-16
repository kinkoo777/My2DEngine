#include "Game.h"

#include "core/Time.h"
#include "events/EventDispatcher.h"
#include "events/WindowCloseEvent.h"
#include "events/WindowResizeEvent.h"
#include "input/KeyCodes.h"
#include "scene/GameObject.h"

#include <glad/glad.h>

static constexpr unsigned int WINDOW_WIDTH = 1280;
static constexpr unsigned int WINDOW_HEIGHT = 720;

// Paths are relative to the executable folder (build/bin/<GameName>/).
// engine/shaders      is copied to  assets/shaders/
// games/<Name>/assets is copied to  assets/
Game::Game()
    : m_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "My New Game"),
      m_Input(m_Window.GetNativeWindow()),
      m_Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag"),
      m_Camera(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)),
      m_QuadGeometry(std::make_shared<Quad>())
{
    m_Window.SetEventCallback([this](Event& event) { OnEvent(event); });

    // Transparency for PNG sprites
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_Renderer.SetBGColor(0.1f, 0.1f, 0.15f, 1.0f);

    // --- Create your objects here ---------------------------------------
    // Coordinates: (0,0) is the top-left corner, x goes right, y goes down.
    //
    // With a texture: put "player.png" in games/<Name>/assets/ and use
    //   std::make_unique<GameObject>(m_QuadGeometry, "assets/player.png");
    auto player = std::make_unique<GameObject>(m_QuadGeometry);
    player->SetColor(0.2f, 0.8f, 0.3f);
    player->GetTransform().SetScale(64.0f, 64.0f);
    player->GetTransform().SetPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

    m_Scene.AddGameObject(std::move(player));   // index 0
}

void Game::Run()
{
    while (m_Running && !m_Window.ShouldClose())
    {
        m_Window.Update();
        Time::Update();
        m_Input.Update();

        Update(Time::GetDeltaTime());

        m_Renderer.Clear();
        Render();
        m_Window.SwapBuffers();
    }
}

void Game::Update(float deltaTime)
{
    if (m_Input.IsKeyJustPressed(Key::Escape))
        m_Running = false;

    // Move the player with WASD / arrow keys
    float dx = 0.0f;
    float dy = 0.0f;

    if (m_Input.IsKeyPressed(Key::W) || m_Input.IsKeyPressed(Key::Up))    dy -= 1.0f;
    if (m_Input.IsKeyPressed(Key::S) || m_Input.IsKeyPressed(Key::Down))  dy += 1.0f;
    if (m_Input.IsKeyPressed(Key::A) || m_Input.IsKeyPressed(Key::Left))  dx -= 1.0f;
    if (m_Input.IsKeyPressed(Key::D) || m_Input.IsKeyPressed(Key::Right)) dx += 1.0f;

    GameObject& player = m_Scene.GetGameObject(0);
    player.GetTransform().Translate(
        dx * m_PlayerSpeed * deltaTime,
        dy * m_PlayerSpeed * deltaTime);
}

void Game::Render()
{
    m_Scene.Render(m_Renderer, m_Shader, m_Camera);
}

void Game::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<WindowCloseEvent>(
        [this](WindowCloseEvent&)
        {
            m_Running = false;
        });

    dispatcher.Dispatch<WindowResizeEvent>(
        [this](WindowResizeEvent& e)
        {
            m_Camera.SetViewportSize(
                static_cast<float>(e.GetWidth()),
                static_cast<float>(e.GetHeight()));
        });
}
