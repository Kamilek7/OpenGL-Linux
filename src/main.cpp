#include "shaders.h"
#include "VAO.h"
#include "EBO.h"
#include <stb/stb_image.h>
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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSwapInterval(0);
    gladLoadGL();
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    std::cout << "urmom2" << std::endl;

    Shaders mainShaders;

    GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2 // Lower triangle
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

    GLuint uniID = glGetUniformLocation(mainShaders.getID(), "scale");

    int width, height, numCh;
    unsigned char* bytes = stbi_load("tex.png", &width, &height, &numCh,0);
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
    glGenerateMipmap(GL_TEXTURE_2D);

    GLuint tex0 = glGetUniformLocation(mainShaders.getID(), "tex0");
    mainShaders.useShader();
    glUniform1i(tex0,0);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        mainShaders.useShader();
        glUniform1f(uniID, 1.5);
        glBindTexture(GL_TEXTURE_2D, texture);
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteTextures(1, &texture);
    vao.remove();
    vbo.remove();
    ebo.remove();
    mainShaders.deleteShader();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
