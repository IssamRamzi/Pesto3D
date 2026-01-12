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
#include "particles/ParticleSystem.h"

#include "math/GeoMa.h"

// #define DRAW_POINTS
#define DRAW_QUADS



const std::string SHADERS_PATH =  "../../assets/shaders/";

void processInput(GLFWwindow *window);

int main() {

	// TODO: refactor batching in class

	Pesto::Window window;
	Pesto::InputManager::Init(window.GetWindowAddr());
	Pesto::Time::Init();
	Pesto::Camera camera(&window, GeoMa::Vector3F{0.0, 0.0, 50.0});
	camera.SetSpeed(.05f);
	camera.SetFov(65);


	f32 vertices[] = {
		-0.5, -0.5,
		0.5, -0.5, 
		0.5, 0.5,
		-0.5, 0.5f
	};

	f32 pointVertex[] = {0,0};

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
#ifdef DRAW_QUADS
	Pesto::VertexBuffer vbo{vertices, 2, 8};
	Pesto::IndexBuffer ebo(indices, 6);

	vao.Bind();
	vao.AddBuffer(vbo, 0, 2, 2 * sizeof(float), (void*)0);

	ebo.Bind();

#else
	Pesto::VertexBuffer vbo{pointVertex, 2, 2};
	vao.Bind();
	vao.AddBuffer(vbo, 0, 2, 2 * sizeof(float), (void*)0);
#endif


	// gpu pipeline
	

	// batching
	Pesto::VertexBuffer instanceVbo;
	instanceVbo.Bind();
	glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(GeoMa::Vector3F), 0);
	
	glVertexAttribDivisor(1,1); // 
	vao.Unbind();

	particleSystem.setEmitterPosition(GeoMa::Vector3F(0.0f, 0.0f, 0.0f));

	glEnable(GL_PROGRAM_POINT_SIZE);


	Pesto::Shader shader{(SHADERS_PATH + "basic.vert").c_str(), (SHADERS_PATH + "basic.frag").c_str()};
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.GetWindowAddr())) {
		Pesto::Time::Update();
		Pesto::InputManager::Update();

		//ImGui::ShowDemoWindow();
		// input
		// -----
		// std::cout << "Before input" << std::endl;
		if(Pesto::InputManager::IsMouseClicked(Pesto::MouseButton::BUTTON_LEFT))
			camera.ProcessMouseInputs();
			
		camera.ProcessKeyboardInputs();
		processInput(window.GetWindowAddr());

		// render
		// ------
		particleSystem.update(Pesto::Time::GetDeltaTime());

		// update l'instancing
		instanceVbo.Bind();
		// glBufferSubData(
		// 			GL_ARRAY_BUFFER, 0, 
        //             particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), 
        //             particleSystem.getPositions().data()
				
		// 		); // Le Cpu attend que le gpu efface les données pour remettre les nouvelles

		
		// Le cpu transfere directement les données dans une place libre du GPU
		glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), nullptr, GL_DYNAMIC_DRAW); 
		glBufferSubData(GL_ARRAY_BUFFER, 0, particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), particleSystem.getPositions().data());


		glClearColor(0.2,0.3,0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.EnableShader();
		shader.SetUniformMat4("camMatrix", camera.CalculateMatrix(0.1, 300));
		// particleSystem.render(shader);
		// std::cout << "After sending size" << std::endl;
		vao.Bind();
#ifdef DRAW_QUADS
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, particleSystem.getParticlesCount());
#else
		glDrawArraysInstanced(GL_POINTS, 0, 1, particleSystem.getParticlesCount());
#endif
		// imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Settings");
		ImGui::Text("Particle System parameters");
		if (ImGui::CollapsingHeader("Camera")) {
				ImGui::Text("FOV %d", camera.GetFov());
				ImGui::Text("Position: (%.2f, %.2f, %.2f)",
							camera.GetPosition().x,
							camera.GetPosition().y,
							camera.GetPosition().z);
				ImGui::Text("Orientation: (%.2f, %.2f, %.2f)",
							camera.GetOrientation().x,
							camera.GetOrientation().y,
							camera.GetOrientation().z);
		}
		if (ImGui::CollapsingHeader("Particles")) {
			ImGui::Text("Count: %d", particleSystem.getParticlesCount());
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window.GetWindowAddr());
		glfwPollEvents();

		window.AddFpsTitle(std::to_string((u16)Pesto::Time::GetFPS()));
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return 0;
}

void processInput(GLFWwindow *window) {
	if (Pesto::InputManager::IsKeyPressed(Pesto::ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
}