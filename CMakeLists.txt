cmake_minimum_required(VERSION 3.10)
project(OpenGL_Demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(
    include
    src
)

add_executable(OpenGL_Demo 
    src/glad.c
    src/main.cpp
    src/shaders.cpp
    src/VBO.cpp
    src/EBO.cpp
    src/VAO.cpp
    
)

target_link_libraries(OpenGL_Demo PRIVATE OpenGL::GL glfw)
