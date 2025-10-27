#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shaders
{
    GLuint shaderProgram;
public:
    
    Shaders(bool debugging=false);
    std::string loadShaderSource(const std::string& filepath);
    void useShader();
    void deleteShader();
};

#endif