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

//osc
#include "osc/OscReceiver.h"

//#define DRAW_POINTS
#define DRAW_QUADS

const std::string SHADERS_PATH =  "../assets/shaders/";
bool drawImgui = true;

void processInput(GLFWwindow *window);

int main() {
	// args in gui
	float attractionForce = 20.0f;
	float attractionRadius = 20.0f;
	GeoMa::Vector3F attractorPosition = GeoMa::Vector3F::ZERO;

	bool shouldUseOscValues = false;

	// TODO: refactor batching in class

	Pesto::Window window;
	Pesto::InputManager::Init(window.GetWindowAddr());
	Pesto::Time::Init();
	Pesto::Camera camera(&window, GeoMa::Vector3F{0.0, 0.0, 50.0});
	camera.SetSpeed(.05f);
	camera.SetFov(65);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	//postprocess
	float quadVertices[] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	unsigned int textureColorBuffer;
	glGenTextures(1, &textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1600, 900, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1600, 900);
	//attach
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR[Framebuffer] : framebuffer not complete" << std::endl;

	vao.Bind();
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

	glVertexAttribDivisor(1,1);

	particleSystem.setEmitterPosition(GeoMa::Vector3F(0.0f, 0.0f, 0.0f));
	glEnable(GL_PROGRAM_POINT_SIZE);

	unsigned int sizeVBO;
	glGenBuffers(1, &sizeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, sizeVBO);
	glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), static_cast<void *>(nullptr));
	glVertexAttribDivisor(2, 1);
	//lifetimes
	unsigned int lifeVBO;
	glGenBuffers(1, &lifeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lifeVBO);
	glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), static_cast<void *>(nullptr));
	glVertexAttribDivisor(3, 1);

	vao.Unbind();
	OscListener osc;
	osc.startListening(7000);
	Pesto::Shader shader{(SHADERS_PATH + "basic.vert").c_str(), (SHADERS_PATH + "basic.frag").c_str()};
	Pesto::Shader screenShader{(SHADERS_PATH + "screen.vert").c_str(), (SHADERS_PATH + "screen.frag").c_str()};
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.GetWindowAddr())) {
		Pesto::Time::Update();
		Pesto::InputManager::Update();

		// setters

		if (shouldUseOscValues) {
			particleSystem.setAttractionForce(attractionForce);
			particleSystem.setAttractionRadius(osc._radius);
			GeoMa::Vector3F posFromOsc;
			posFromOsc.x = (osc._attractorX * 80.0f) - 40.0f;
			posFromOsc.y = (osc._attractorY * 60.0f) - 30.0f;
			posFromOsc.z = 0.0f;
			particleSystem.setAttractionPosition(posFromOsc);
		} else {
			particleSystem.setAttractionForce(attractionForce);
			particleSystem.setAttractionRadius(attractionRadius);
			particleSystem.setAttractionPosition(attractorPosition);
		}


		//ImGui::ShowDemoWindow();
		// input
		// -----
		// std::cout << "Before input" << std::endl;
		if(Pesto::InputManager::IsKeyDown(Pesto::Key::LCTRL))
			camera.ProcessMouseInputs();

		if (Pesto::InputManager::IsKeyPressed(Pesto::Key::R))
			particleSystem.resetAllParticles();

		camera.ProcessKeyboardInputs();
		processInput(window.GetWindowAddr());

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0,0.0,0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		//positions
		glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), particleSystem.getPositions().data());
		//sizes
		glBindBuffer(GL_ARRAY_BUFFER, sizeVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, particleSystem.getParticlesCount() * sizeof(float),
			particleSystem.getSizes().data());
		//lifetimes
		glBindBuffer(GL_ARRAY_BUFFER, lifeVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, particleSystem.getParticlesCount() * sizeof(float),
			particleSystem.getLifetimes().data());
		glBindBuffer(GL_ARRAY_BUFFER, lifeVBO);




		shader.EnableShader();
		shader.SetUniformMat4("camMatrix", camera.CalculateMatrix(0.1, 300));
		//shader.SetUniform4f("Color", {1.0f, 0.5f, 0.2f, 1.0f * particleSystem.lifespan});
		particleSystem.render(shader);
		vao.Bind();
#ifdef DRAW_QUADS
		glEnable(GL_BLEND);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, particleSystem.getParticlesCount());
		glDisable(GL_BLEND);
#else
		glEnable(GL_BLEND);
		glDrawArraysInstanced(GL_POINTS, 0, 1, particleSystem.getParticlesCount());
		glDisable(GL_BLEND);
#endif

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		screenShader.EnableShader();
		glBindVertexArray(quadVAO);
		glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Settings");
		ImGui::Text("Particle System parameters");
		if (ImGui::CollapsingHeader("Particles")) {
			ImGui::Text("Count: %d", particleSystem.getParticlesCount());
		}
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
		if (ImGui::CollapsingHeader("Forces")) {
			ImGui::SliderFloat3("Attraction Position", &attractorPosition.x, -50.f, 50.f);
			ImGui::SliderFloat("Attraction Force", &attractionForce, 0.f, 100.f);
			ImGui::SliderFloat("Attraction Radius", &attractionRadius, 0.f, 250.f);
		}
		if (ImGui::CollapsingHeader("OSC")) {
			ImGui::Checkbox("Use OSC", &shouldUseOscValues);
		}
		ImGui::End();
		ImGui::Render();
		if (drawImgui)
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window.GetWindowAddr());
		glfwPollEvents();

		window.AddFpsTitle(std::to_string((u32)Pesto::Time::GetFPS()));
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
	if (Pesto::InputManager::IsKeyPressed(Pesto::Key::TAB)) {
		drawImgui = !drawImgui;
	}
}