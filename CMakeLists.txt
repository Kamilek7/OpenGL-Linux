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
    GIT_TAG        1.0.1  # or whichever stable release you want
)
find_package(OpenGL REQUIRED)


FetchContent_MakeAvailable(glfw glm)

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
)

target_include_directories(OpenGL_Demo PUBLIC src include)
target_link_libraries(OpenGL_Demo PRIVATE glfw glm)

file(GLOB FILES "${CMAKE_SOURCE_DIR}/src/*.vert" "${CMAKE_SOURCE_DIR}/src/*.frag" "${CMAKE_SOURCE_DIR}/src/*.png")

foreach(FILE ${FILES})
    get_filename_component(NAME ${FILE} NAME)
    add_custom_command(
        TARGET OpenGL_Demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${FILE}
            $<TARGET_FILE_DIR:OpenGL_Demo>/${NAME}
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
