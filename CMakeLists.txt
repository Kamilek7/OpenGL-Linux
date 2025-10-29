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
find_package(OpenGL REQUIRED)

FetchContent_MakeAvailable(glfw)

add_executable(OpenGL_Demo 
    src/glad.c
    src/main.cpp
    src/shaders.cpp
    src/VBO.cpp
    src/EBO.cpp
    src/VAO.cpp
    
)

target_include_directories(OpenGL_Demo PUBLIC src include)
target_link_libraries(OpenGL_Demo PRIVATE glfw)

file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/src/*.vert" "${CMAKE_SOURCE_DIR}/src/*.frag")

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME)
    add_custom_command(
        TARGET OpenGL_Demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SHADER_FILE}
            $<TARGET_FILE_DIR:OpenGL_Demo>/${SHADER_NAME}
    )
endforeach()


if (WIN32)
    target_link_libraries(OpenGL_Demo PRIVATE opengl32 gdi32 user32 shell32)
elseif(APPLE)
    find_library(OpenGL_LIB OpenGL)
    target_link_libraries(OpenGL_Demo PRIVATE ${OpenGL_LIB})
else()
    target_link_libraries(OpenGL_Demo PRIVATE OpenGL::GL)
endif()
