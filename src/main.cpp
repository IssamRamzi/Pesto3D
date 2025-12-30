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
#include "math/GeoMa.h"

const std::string SHADERS_PATH =  "../assets/shaders/";

void processInput(GLFWwindow *window);

int main() {
	Pesto::Window window;
	Pesto::Time::Init();

	f32 vertices[] = {
		-0.05f, -0.05f, 0.0f,
		0.05f, -0.05f, 0.0f,
		0.05f,  0.05f, 0.0f,
	};

	//imgui init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindowAddr(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();

	Pesto::VertexArrays vao;
	Pesto::VertexBuffer vbo{vertices, 3, 9};
	vao.Bind();
	vao.AddBuffer(vbo, 0, 3, 3 * sizeof(float), (void*)0);
	vao.Unbind();

	//instancing test
	GeoMa::Vector3F translations[100];
	int idx = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y+=2) {
		for (int x = -10; x < 10; x+=2) {
			GeoMa::Vector3F translation;
			translation.x = (float)x / 10.0f;
			translation.y = (float)y / 10.0f;
			translations[idx++] = translation;
		}
	}


	Pesto::Shader shader{(SHADERS_PATH + "basic.vert").c_str(), (SHADERS_PATH + "basic.frag").c_str()};

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.GetWindowAddr())) {
		Pesto::Time::Update();

		//ImGui::ShowDemoWindow();
		// input
		// -----
		processInput(window.GetWindowAddr());

		// render
		// ------
		shader.EnableShader();
		for (unsigned int i = 0; i < 100; i++) {
			std::string uniformName = "offsets[" + std::to_string(i) + "]";
			shader.SetUniform3f(uniformName.c_str(), translations[i]);
		}
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		vao.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//instancing
		glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 100);

		// imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Settings");
		ImGui::Text("Particle System parameters");
		ImGui::End();
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
