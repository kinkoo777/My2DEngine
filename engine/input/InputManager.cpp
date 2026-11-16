#include "input/InputManager.h"

InputManager::InputManager(GLFWwindow *window)
{
    m_Window = window;

    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++)
    {
        m_CurrentKeys[key] = false;
        m_PreviousKeys[key] = false;
    }

    for (int button = GLFW_MOUSE_BUTTON_1;
         button <= GLFW_MOUSE_BUTTON_LAST;
         button++)
    {
        m_CurrentMouseButtons[button] = false;
        m_PreviousMouseButtons[button] = false;
    }
}

bool InputManager::IsKeyPressed(Key key)
{
    return m_CurrentKeys[ToGLFWKey(key)];
}
void InputManager::Update()
{
    m_PreviousKeys = m_CurrentKeys;
    m_PreviousMouseButtons = m_CurrentMouseButtons;

    for (auto& key : m_CurrentKeys)
    {
        key.second = glfwGetKey(m_Window, key.first) == GLFW_PRESS;
    }

    for (auto& button : m_CurrentMouseButtons)
    {
        button.second =
            glfwGetMouseButton(m_Window, button.first) == GLFW_PRESS;
    }
}

bool InputManager::IsKeyJustPressed(Key key)
{
    return !m_PreviousKeys[ToGLFWKey(key)] &&
            m_CurrentKeys[ToGLFWKey(key)];
}

bool InputManager::IsMouseButtonPressed(MouseButton button)
{
    return m_CurrentMouseButtons[ToGLFWMouseButton(button)];
}

bool InputManager::IsMouseButtonReleased(MouseButton button)
{
    return m_PreviousMouseButtons[ToGLFWMouseButton(button)] &&
          !m_CurrentMouseButtons[ToGLFWMouseButton(button)];
}

bool InputManager::IsMouseButtonJustPressed(MouseButton button)
{
    return !m_PreviousMouseButtons[ToGLFWMouseButton(button)] &&
            m_CurrentMouseButtons[ToGLFWMouseButton(button)];
}

Vector2 InputManager::GetMousePosition() const
{
    double x, y;

    glfwGetCursorPos(m_Window, &x, &y);

    return Vector2(
        static_cast<float>(x),
        static_cast<float>(y)
    );
}

bool InputManager::IsKeyReleased(Key key)
{
    return m_PreviousKeys[ToGLFWKey(key)] &&
           !m_CurrentKeys[ToGLFWKey(key)];
}

int InputManager::ToGLFWKey(Key key) const
{
    switch (key)
    {
    case Key::W:
        return GLFW_KEY_W;

    case Key::A:
        return GLFW_KEY_A;

    case Key::S:
        return GLFW_KEY_S;

    case Key::D:
        return GLFW_KEY_D;

    case Key::Space:
        return GLFW_KEY_SPACE;

    case Key::Escape:
        return GLFW_KEY_ESCAPE;

    case Key::Up:
        return GLFW_KEY_UP;

    case Key::Down:
        return GLFW_KEY_DOWN;

    case Key::Left:
        return GLFW_KEY_LEFT;

    case Key::Right:
        return GLFW_KEY_RIGHT;
    }

    return GLFW_KEY_UNKNOWN;
}

int InputManager::ToGLFWMouseButton(MouseButton button) const
{
    switch (button)
    {
    case MouseButton::Left:
        return GLFW_MOUSE_BUTTON_LEFT;

    case MouseButton::Right:
        return GLFW_MOUSE_BUTTON_RIGHT;

    case MouseButton::Middle:
        return GLFW_MOUSE_BUTTON_MIDDLE;
    }

    return -1;
}