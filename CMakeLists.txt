cmake_minimum_required(VERSION 3.20)

project(My2DEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(glad STATIC
    vendor/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    vendor/glad/include
)

add_executable(My2DEngine
    src/main.cpp
    framework/shader/src/Shader.cpp
    framework/shader/renderer/src/IndexBuffer.cpp
    framework/shader/renderer/src/Renderer.cpp
    framework/shader/renderer/src/VertexArray.cpp
    framework/shader/renderer/src/VertexBuffer.cpp
    framework/shader/renderer/src/VertexBufferLayout.cpp
    framework/shader/renderer/src/VertexBufferElement.cpp
    framework/transform/src/Transform.cpp
    framework/time/src/Time.cpp
    framework/core/src/GameObject.cpp
)

target_link_libraries(My2DEngine PRIVATE
    glad
    glfw
    OpenGL::GL
    glm::glm
)