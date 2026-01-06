#include <iostream>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "core/Window.h"
#include "core/InputManager.h"
#include "core/Time.h"
#include "core/Camera.h"

#include "graphics/Shader.h"
#include "graphics/VertexArrays.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/ParticleSystem.h"

#include "math/GeoMa.h"

const std::string SHADERS_PATH =  "../../assets/shaders/";

void processInput(GLFWwindow *window);

int main() {

	// TODO: refactor batching in class

	Pesto::Window window;
	Pesto::Time::Init();
	Pesto::Camera camera(&window, GeoMa::Vector3F{0.0, 0.0, 12.0});
	camera.SetSpeed(5.0f);
	camera.SetFov(65);


	f32 vertices[] = {
		-0.5, -0.5,
		0.5, -0.5, 
		0.5, 0.5,
		-0.5, 0.5f
	};

	u32 indices[] = {0,1,2,2,3,0};

	//imgui init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindowAddr(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();

	Pesto::ParticleSystem particleSystem;

	Pesto::VertexArrays vao;
	Pesto::VertexBuffer vbo{vertices, 2, 8};
	Pesto::IndexBuffer ebo(indices, 6);

	// gpu pipeline
	vao.Bind();
	vao.AddBuffer(vbo, 0, 2, 2 * sizeof(float), (void*)0);
	ebo.Bind();

	// batching
	Pesto::VertexBuffer instanceVbo;
	instanceVbo.Bind();
	glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(GeoMa::Vector3F), 0);
	
	glVertexAttribDivisor(1,1); // 
	vao.Unbind();

	particleSystem.setEmitterPosition(GeoMa::Vector3F(0.0f, 0.0f, 0.0f));


	Pesto::Shader shader{(SHADERS_PATH + "basic.vert").c_str(), (SHADERS_PATH + "basic.frag").c_str()};

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.GetWindowAddr())) {
		Pesto::Time::Update();

		//ImGui::ShowDemoWindow();
		// input
		// -----
		camera.ProcessKeyboardInputs();
    	camera.ProcessMouseInputs();

		processInput(window.GetWindowAddr());

		// render
		// ------
		particleSystem.update(Pesto::Time::GetDeltaTime());

		// update l'instancing
		instanceVbo.Bind();
		glBufferSubData(
					GL_ARRAY_BUFFER, 0, 
                    particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), 
                    particleSystem.getPositions().data()
				
				);

		glClearColor(0.2,0.3,0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.EnableShader();
		shader.SetUniformMat4("camMatrix", camera.CalculateMatrix(0.1, 100));
		vao.Bind();
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, particleSystem.getParticlesCount());

		



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