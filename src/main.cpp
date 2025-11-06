#include "VAO.h"
#include "EBO.h"
#include <math.h>
#include "texture.h"
#include "camera.h"
#include "mesh.h"

void resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{


// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


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

	Texture textures[]
	{
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

    Shaders mainShaders("default.vert", "default.frag");

    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

    Mesh floor(verts, ind, tex);

    Shaders lightShader("light.vert", "light.frag");

    std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices)/sizeof(Vertex));
    std::vector<GLuint> lightInds(lightIndices, lightIndices+sizeof(lightIndices)/sizeof(GLuint));
    Mesh light(lightVerts, lightInds, tex);

    glm::vec4 lightColor(1.0f,1.0f,1.0f, 1.0f);
    glm::vec3 lightPos(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel=glm::translate(lightModel, lightPos);

    glm::vec3 objectPos = glm::vec3(0.0f,0.0f,0.0f);
    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel=glm::translate(objectModel, objectPos);

    
    lightShader.useShader();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    mainShaders.useShader();
	glUniformMatrix4fv(glGetUniformLocation(mainShaders.getID(), "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(mainShaders.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(mainShaders.getID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    glEnable(GL_DEPTH_TEST);

    Camera camera(glm::vec3(0.0f,0.0f, 2.0f));

    double prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        double crnt = glfwGetTime();
        while (crnt-prevTime < 1.0f/60.0f)
            crnt = glfwGetTime();
        prevTime=crnt;
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.inputs(window, WINDOW_WIDTH, WINDOW_HEIGHT);
        camera.updateMat(45.0f, 0.1f, 100.0f, WINDOW_WIDTH, WINDOW_HEIGHT);

        floor.draw(mainShaders, camera);
        light.draw(lightShader, camera);

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    lightShader.deleteShader();
    mainShaders.deleteShader();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
