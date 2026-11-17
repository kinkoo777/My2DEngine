
#include "core/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

#include "events/WindowResizeEvent.h"
#include "events/KeyPressedEvent.h"
#include "events/KeyReleasedEvent.h"
#include "events/WindowCloseEvent.h"
Window::Window(unsigned int width, unsigned int height, const char *title)
    : m_Window(nullptr),
      m_Width(width),
      m_Height(height)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    m_Window = glfwCreateWindow(
        m_Width,
        m_Height,
        title,
        nullptr,
        nullptr);

    if (!m_Window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    // Create OpenGL context
    glfwMakeContextCurrent(m_Window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
        glfwTerminate();

        throw std::runtime_error("Failed to initialize GLAD");
    }

    // Initial viewport
    int framebufferWidth;
    int framebufferHeight;

    glfwGetFramebufferSize(
        m_Window,
        &framebufferWidth,
        &framebufferHeight);

    glViewport(
        0,
        0,
        framebufferWidth,
        framebufferHeight);

    // Connect Window instance to GLFW
    glfwSetWindowUserPointer(m_Window, this);

    glfwSetWindowCloseCallback(
        m_Window,
        [](GLFWwindow *window)
        {
            Window *instance = static_cast<Window *>(
                glfwGetWindowUserPointer(window));

            if (!instance || !instance->m_EventCallback)
                return;

            WindowCloseEvent event;
            instance->m_EventCallback(event);
        });

    // Keyboard callback
    glfwSetKeyCallback(
        m_Window,
        [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            Window *instance = static_cast<Window *>(
                glfwGetWindowUserPointer(window));

            if (!instance || !instance->m_EventCallback)
                return;

            if (action == GLFW_PRESS)
            {
                KeyPressedEvent event(key, 0);
                instance->m_EventCallback(event);
            }
            else if (action == GLFW_REPEAT)
            {
                KeyPressedEvent event(key, 1);
                instance->m_EventCallback(event);
            }
            else if (action == GLFW_RELEASE)
            {
                KeyReleasedEvent event(key);
                instance->m_EventCallback(event);
            }
        });

    // Window resize callback
    glfwSetWindowSizeCallback(
        m_Window,
        [](GLFWwindow *window, int width, int height)
        {
            Window *instance = static_cast<Window *>(
                glfwGetWindowUserPointer(window));

            if (!instance)
                return;

            instance->m_Width = static_cast<unsigned int>(width);
            instance->m_Height = static_cast<unsigned int>(height);

            if (instance->m_EventCallback)
            {
                WindowResizeEvent event(
                    instance->m_Width,
                    instance->m_Height);

                instance->m_EventCallback(event);
            }
        });

    glfwSetFramebufferSizeCallback(
        m_Window,
        [](GLFWwindow *, int width, int height)
        {
            glViewport(0, 0, width, height);
        });
}

Window::~Window()
{
    if (m_Window)
    {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }

    glfwTerminate();
}

void Window::Update()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

unsigned int Window::GetWidth() const
{
    return m_Width;
}

unsigned int Window::GetHeight() const
{
    return m_Height;
}

GLFWwindow *Window::GetNativeWindow() const
{
    return m_Window;
}

void Window::SetEventCallback(const EventCallback &callback)
{
    m_EventCallback = callback;
}
