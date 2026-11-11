#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../framework/shader/Shader.h"
#include "../framework/shader/renderer/IndexBuffer.h"
#include "../framework/shader/renderer/VertexBuffer.h"
#include "../framework/shader/renderer/Renderer.h"
#include "../framework/shader/renderer/VertexArray.h"
#include "../framework/shader/renderer/VertexBufferLayout.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../framework/transform/Transform.h"
#include "../framework/time/Time.h"
#include "../framework/core/GameObject.h"

#include <iostream>

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Use Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window
    GLFWwindow *window = glfwCreateWindow(
        1280,
        720,
        "My 2D Engine",
        nullptr,
        nullptr);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    // Set OpenGL context
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }
    {

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 0
            0.5f, -0.5f,0.0f, 1.0f, 0.0f,   // 1
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f,   // 2
            -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,    // 3
        };


        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};


        Shader shader(
            "assets/shaders/basic.vert",
            "assets/shaders/basic.frag");


        Renderer renderer;


        float test = 0;

        GameObject square(vertices, sizeof(vertices), indices, sizeof(indices), 6);

        // Main Game Loop
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();
            
            if (test == 360) {
                test = 0;
            }
            square.GetTransform().SetRotation(test);

            test++;

            renderer.Draw(square, shader);



            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}