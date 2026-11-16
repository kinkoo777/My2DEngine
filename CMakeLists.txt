cmake_minimum_required(VERSION 3.20)

project(My2DEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

# ---------------------------------------------------------------------------
# Third-party code (vendor/)
# ---------------------------------------------------------------------------
add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)

add_library(stb_image STATIC vendor/stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC vendor)   # -> #include "stb_image/stb_image.h"

# ---------------------------------------------------------------------------
# The engine (engine/)  ->  static library every game links against
# ---------------------------------------------------------------------------
add_subdirectory(engine)

# ---------------------------------------------------------------------------
# Games (games/<Name>/)
#
# Every folder inside games/ becomes its own executable named after the folder.
# All .cpp files in that folder (and its subfolders) are compiled automatically.
# Folders starting with "_" (like games/_Template) are skipped.
#
# After each build the game's files are laid out like this:
#   build/bin/<Name>/<Name>              the executable
#   build/bin/<Name>/assets/shaders/     engine shaders (engine/shaders)
#   build/bin/<Name>/assets/...          the game's own assets (games/<Name>/assets)
# ---------------------------------------------------------------------------
file(GLOB GAME_DIRS LIST_DIRECTORIES true CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/games/*")

foreach(GAME_DIR ${GAME_DIRS})
    if(NOT IS_DIRECTORY "${GAME_DIR}")
        continue()
    endif()

    get_filename_component(GAME_NAME "${GAME_DIR}" NAME)
    if(GAME_NAME MATCHES "^_")
        continue()
    endif()

    file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "${GAME_DIR}/*.cpp")
    if(NOT GAME_SOURCES)
        continue()
    endif()

    add_executable(${GAME_NAME} ${GAME_SOURCES})
    target_include_directories(${GAME_NAME} PRIVATE "${GAME_DIR}")
    target_link_libraries(${GAME_NAME} PRIVATE engine)

    set_target_properties(${GAME_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${GAME_NAME}"
    )

    # Copy engine shaders + game assets next to the executable after every build
    add_custom_command(TARGET ${GAME_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/engine/shaders"
                "$<TARGET_FILE_DIR:${GAME_NAME}>/assets/shaders"
    )
    if(IS_DIRECTORY "${GAME_DIR}/assets")
        add_custom_command(TARGET ${GAME_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${GAME_DIR}/assets"
                    "$<TARGET_FILE_DIR:${GAME_NAME}>/assets"
        )
    endif()

    # `cmake --build build --target run_<Name>` builds and starts the game
    add_custom_target(run_${GAME_NAME}
        COMMAND $<TARGET_FILE:${GAME_NAME}>
        WORKING_DIRECTORY "$<TARGET_FILE_DIR:${GAME_NAME}>"
        DEPENDS ${GAME_NAME}
        USES_TERMINAL
    )

    message(STATUS "Game found: ${GAME_NAME}")
endforeach()
