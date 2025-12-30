#include <iostream>

#include "core/Window.h"
#include "core/InputManager.h"

#include "graphics/VertexArrays.h"
#include "graphics/VertexBuffer.h"
#include "graphics/Shader.h"
#include "core/Time.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

const std::string SHADERS_PATH =  "../assets/shaders/";

void processInput(GLFWwindow *window);

int main() {
	Pesto::Window window;
	Pesto::Time::Init();

	f32 vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
	};

	//imgui init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindowAddr(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	Pesto::VertexArrays vao;
	Pesto::VertexBuffer vbo{vertices, 3, 9};
	vao.Bind();
	vao.AddBuffer(vbo, 0, 3, 3 * sizeof(float), (void*)0);
	vao.Unbind();

	Pesto::Shader shader{(SHADERS_PATH + "basic.vert").c_str(), (SHADERS_PATH + "basic.frag").c_str()};

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.GetWindowAddr())) {
		Pesto::Time::Update();
		// imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		// input
		// -----
		processInput(window.GetWindowAddr());

		// render
		// ------
		shader.EnableShader();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window.GetWindowAddr());
		glfwPollEvents();

		window.AddFpsTitle(std::to_string((u16)Pesto::Time::GetFPS()));
	}
	return 0;
}

void processInput(GLFWwindow *window) {
	if (Pesto::InputManager::IsKeyPressed(Pesto::ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}
