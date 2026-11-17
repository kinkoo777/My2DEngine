# The engine library. Every .cpp inside engine/ is picked up automatically,
# so adding a new engine file only needs a CMake re-run.

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(engine STATIC ${ENGINE_SOURCES})

# Includes are written relative to engine/, e.g.
#   #include "renderer/Renderer.h"
#   #include "input/InputManager.h"
target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(engine PUBLIC
    glad
    stb_image
    ${MY2DENGINE_GLFW_TARGET}
    OpenGL::GL
    glm::glm
)
