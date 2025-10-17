cmake_minimum_required(VERSION 3.10)
project(OpenGL_Demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(include)

add_executable(OpenGL_Demo 
    src/main.cpp
    src/glad.c
)

target_link_libraries(OpenGL_Demo PRIVATE OpenGL::GL glfw)
