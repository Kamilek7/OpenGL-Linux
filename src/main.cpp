#include "VAO.h"
#include "EBO.h"
#include <math.h>
#include "texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    if (!glfwInit()) 
    {
        std::cerr << "GLFW init fail\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", nullptr, nullptr);
    if (!window) 
    {
        std::cerr << "Failed to create a window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSwapInterval(0);
    gladLoadGL();
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    Shaders mainShaders;

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


    VAO vao;
    vao.bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.linkAttributes(vbo,0, 3, GL_FLOAT, 8*sizeof(float), (void*)(0));
    vao.linkAttributes(vbo,1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float)));
    vao.linkAttributes(vbo,2, 2, GL_FLOAT, 8*sizeof(float), (void*)(6*sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
    Texture l("tex.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    l.texUnit(mainShaders, "tex0", 0);
    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mainShaders.useShader();

        double crnt = glfwGetTime();
        if (crnt-prevTime >= 1/60)
        {
            rotation+=0.05f;
            prevTime = crnt;
        }
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f,1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH/WINDOW_HEIGHT), 0.1f, 100.0f);
        int modelLoc = glGetUniformLocation(mainShaders.getID(), "model");
        int viewLoc = glGetUniformLocation(mainShaders.getID(), "view");
        int projLoc = glGetUniformLocation(mainShaders.getID(), "proj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
        l.bind();
        vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    l.remove();
    vao.remove();
    vbo.remove();
    ebo.remove();
    mainShaders.deleteShader();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
