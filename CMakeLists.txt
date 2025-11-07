cmake_minimum_required(VERSION 3.10)
project(OpenGL_Demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.8
)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1 
)

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG        v5.3.1 
)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw glm assimp)

find_package(OpenGL REQUIRED)

add_executable(OpenGL_Demo 
    src/glad.c
    src/main.cpp
    src/shaders.cpp
    src/VBO.cpp
    src/EBO.cpp
    src/VAO.cpp
    src/stb_image.cpp
    src/texture.cpp
    src/camera.cpp
    src/mesh.cpp
    src/board.cpp
    src/importer.cpp
    src/model.cpp
    src/object.cpp
)

target_include_directories(OpenGL_Demo PUBLIC src include)
target_link_libraries(OpenGL_Demo PRIVATE glfw glm assimp)

add_custom_command(TARGET OpenGL_Demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:OpenGL_Demo>"
        "${CMAKE_SOURCE_DIR}/src/OpenGL_Demo${CMAKE_EXECUTABLE_SUFFIX}"
    VERBATIM
)

if (WIN32)
    target_link_libraries(OpenGL_Demo PRIVATE opengl32 gdi32 user32 shell32)
elseif(APPLE)
    find_library(OpenGL_LIB OpenGL)
    target_link_libraries(OpenGL_Demo PRIVATE ${OpenGL_LIB})
else()
    target_link_libraries(OpenGL_Demo PRIVATE OpenGL::GL)
endif()
