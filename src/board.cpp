#include "board.h"

unsigned int WINDOW_WIDTH = 800;
unsigned int WINDOW_HEIGHT = 800;

void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	WINDOW_HEIGHT=height;
	WINDOW_WIDTH=width;
}

GameComponents::GameComponents()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW init fault!";
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	gladLoadGL();
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	shaderProgram = Shaders("resources/shaders/default.vert", "resources/shaders/default.frag");
	shaderProgram.useShader();
	glUniform4f(glGetUniformLocation(shaderProgram.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	camera = Camera(glm::vec3(0.0f, 0.2f, 0.5f));

	int randCount = 50;
	float offset = -10.0f;
	float border = 4.0f;

	float division = (float)(randCount/2)/(border-0.1f);
	float speedDiv = 45.0f;
	glUniform3f(glGetUniformLocation(shaderProgram.getID(), "lightPos"), 0.0f, 0.0f, offset);
	
	for (int i=0; i<1000;i++)
	{

		objects.push_back(new Ball(&importer, glm::vec3(0.0f,0.0f,offset), (rand()%randCount)/10.0f + 0.3, glm::vec3((rand()%randCount-randCount/2)/division,(rand()%randCount-randCount/2)/division,offset+ (rand()%randCount-randCount/2)/division), glm::vec3((1-2*rand()%2)*(rand()%randCount+1)/speedDiv, (1-2*rand()%2)*(rand()%randCount+1)/speedDiv,(1-2*rand()%2)*(rand()%randCount+1)/speedDiv),glm::vec3((rand()%255)/255.0f, (rand()%255)/255.0f,(rand()%255)/255.0f), border));
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
	// objects.push_back(new ingameObject("resources/models/sbunny/scene.gltf", &importer));
}

void GameComponents::inputs()
{
	
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && buttonPressFlag)
	{
		gravity = !gravity;
		buttonPressFlag = false;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE && !buttonPressFlag)
	{
		buttonPressFlag = true;
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && HbuttonPressFlag)
	{
		aero = !aero;
		HbuttonPressFlag = false;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE && !HbuttonPressFlag)
	{
		HbuttonPressFlag = true;
	}

	camera.inputs(window, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GameComponents::render()
{

	glfwPollEvents();
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.updateMat(45.0f, 0.1f, 100.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
	for (int i = 0; i < objects.size(); i++)
	{
		// Brany jest fpsLimit albo czas renderu poprzedniej klatki, nie jest to idealne ale dziala
		objects[i]->process(std::max(fpsTime, 0.0), shaderProgram, camera, gravity, aero);
	}
	this->inputs();
	// Jak na razie nie jest potrzebny ale moze sie przydac w przyszlosci
	Clock += (float)fpsTime;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Example");
	ImGui::Text("Hello, world!");
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
	duration = glfwGetTime() - previousTime;
	
	if ( duration< fpsTime)
	{
		double remaining = (fpsTime - duration) * 1000.0;
        std::this_thread::sleep_for(std::chrono::milliseconds((int)remaining));
	}
	previousTime = glfwGetTime();
}

void GameComponents::end()
{
	shaderProgram.deleteShader();
	glfwDestroyWindow(window);
	glfwTerminate();
}