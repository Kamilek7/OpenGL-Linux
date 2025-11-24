#include "GUIDrawn.h"

GuiModule::GuiModule(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void GuiModule::draw(bool* gravity, bool* aero)
{
    ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Ustawienia");
	ImGui::Text("Sily:");
	ImGui::Checkbox("Grawitacja", gravity);
	ImGui::Checkbox("Opor aerodynamiczny", aero);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}