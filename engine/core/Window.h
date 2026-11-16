
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

#include "events/Event.h"

class Window
{
public:
    using EventCallback = std::function<void(Event&)>;

    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();

    void Update();
    void SwapBuffers();

    bool ShouldClose() const;

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

    GLFWwindow* GetNativeWindow() const;

    void SetEventCallback(const EventCallback& callback);

private:
    GLFWwindow* m_Window;

    unsigned int m_Width;
    unsigned int m_Height;

    EventCallback m_EventCallback;
};
