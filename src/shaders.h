#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shaders
{

public:
    GLuint shaderProgram;
    Shaders(bool debugging=false);
    std::string loadShaderSource(const std::string& filepath);
};

