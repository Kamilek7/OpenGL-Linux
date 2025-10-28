#include "shaders.h"
#include "VAO.h"
#include "EBO.h"

#include <math.h>


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

    Shaders mainShaders;

    GLfloat vertices[] =
    { //               COORDINATES                  /     COLORS           //
        -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.3f, 0.8f,  0.02f, // Lower right corner
        0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.3f, 0.3f,  0.8f, // Upper corner
        -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.9f, 0.9f, // Inner left
        0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.9f, 0.9f, // Inner right
        0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.9f, 0.9f,  0.9f  // Inner down
    };


    GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Upper triangle
		5, 4, 1 // Lower right triangle
	};

    VAO vao;
    vao.bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.linkAttributes(vbo,0, 3, GL_FLOAT, 6*sizeof(float), (void*)(0));
    vao.linkAttributes(vbo,1, 3, GL_FLOAT, 6*sizeof(float), (void*)(3*sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    GLuint uniID = glGetUniformLocation(mainShaders.getID(), "scale");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        mainShaders.useShader();
        glUniform1f(uniID, 1.5);
        vao.bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.remove();
    vbo.remove();
    ebo.remove();
    mainShaders.deleteShader();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
