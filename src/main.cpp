#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>


std::string loadShaderSource(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) throw std::runtime_error("Cannot open file: " + filepath);

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}



void resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    if (!glfwInit()) 
    {
        std::cerr << "GLFW init fail\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (!window) 
    {
        std::cerr << "Failed to create a window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    gladLoadGL();
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    std::string src = loadShaderSource("../src/default.vert");
    const char* srcVert = src.c_str();
    glShaderSource(vertShader, 1, &srcVert, nullptr);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    src = loadShaderSource("../src/default.frag");
    const char* srcFrag = src.c_str();
    std::cout << srcFrag << std::endl;
    glShaderSource(fragShader, 1, &srcFrag, nullptr);
    glCompileShader(fragShader);

	int bufflen;
	glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &bufflen);
	GLchar* log_string = new char[bufflen + 1];
	glGetShaderInfoLog(fragShader, bufflen, 0, log_string);
	std::cout << log_string << std::endl << std::endl;

	//glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &bufflen);
	//GLchar * log_string = new char[bufflen + 1];
	//glGetShaderInfoLog(vertexShader, bufflen, 0, log_string);
	//std::cout << log_string;

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
