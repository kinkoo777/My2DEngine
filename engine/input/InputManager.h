#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>
#include "input/KeyCodes.h"

#include "input/MouseButton.h"
#include "math/Vector2.h"

class InputManager
{
public:
    InputManager(GLFWwindow* window);

    bool IsKeyPressed(Key key);
    bool IsKeyJustPressed(Key key);
    bool IsKeyReleased(Key key);

    bool IsMouseButtonPressed(MouseButton button);
    bool IsMouseButtonJustPressed(MouseButton button);
    bool IsMouseButtonReleased(MouseButton button);

    Vector2 GetMousePosition() const;

    void Update();

private:
    GLFWwindow* m_Window;

    int ToGLFWKey(Key key) const;

    std::unordered_map<int, bool> m_CurrentKeys;
    std::unordered_map<int, bool> m_PreviousKeys;

    int ToGLFWMouseButton(MouseButton button) const;

    std::unordered_map<int, bool> m_CurrentMouseButtons;
    std::unordered_map<int, bool> m_PreviousMouseButtons;
};