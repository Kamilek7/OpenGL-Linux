#include "board.h"

GameComponents::GameComponents()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	shaderProgram = Shaders("resources/shaders/default.vert", "resources/shaders/default.frag");
	shaderProgram.useShader();
	glUniform4f(glGetUniformLocation(shaderProgram.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.getID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	camera = Camera(glm::vec3(0.0f, 0.2f, 0.5f));
	objects.push_back(new ingameObject("resources/sbunny/scene.gltf", &importer));
	//objects.push_back(new ingameObject("resources/statue/scene.gltf", &importer));
}

void GameComponents::render()
{

	glfwPollEvents();
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.updateMat(45.0f, 0.1f, 100.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
	while (duration <= fpsTime)
	{
		current = glfwGetTime();
		duration = current - previousTime;
	}
	duration = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->process(fpsTime, shaderProgram, camera);
	}
	camera.inputs(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	Clock += (float)fpsTime;
	glfwSwapBuffers(window);
	previousTime = glfwGetTime();
}

void GameComponents::end()
{
	shaderProgram.deleteShader();
	glfwDestroyWindow(window);
	glfwTerminate();
}