//
// Created by Issam on 26/01/2026.
//

#include "Application.h"

#include <algorithm>

#include "core/InputManager.h"
#include "core/Time.h"
#include "graphics/Shader.h"
#include "graphics/VertexArrays.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "graphics/CubeMap.h"
#include "graphics/FrameBuffer.h"


#define DRAW_QUADS
const std::string SHADERS_PATH = "../assets/shaders/";

void initUI(GLFWwindow* window) {
	//imgui init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();
}


void Application::Initialize() {
    Pesto::InputManager::Init(window.GetWindowAddr());
    Pesto::Time::Init();

	camera = Pesto::Camera(&window, GeoMa::Vector3F{0.0, 0.0, 50.0});
	camera.SetSpeed(.05f);
	camera.SetFov(65);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Application::Run() {
	f32 vertices[] = {
		-0.5, -0.5,
		0.5, -0.5,
		0.5, 0.5,
		-0.5, 0.5f
	};

	u32 indices[] = {0,1,2,2,3,0};

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
	// gpu pipeline

	Pesto::VertexArrays quadVAO;
	quadVAO.Bind();
	Pesto::VertexBuffer quadVBO{quadVertices, 4, 4 * 6};
	quadVAO.AddBuffer(quadVBO, 0, 2, 4 * sizeof(float), (void*)0);
	quadVAO.AddBuffer(quadVBO, 1, 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));quadVAO.Unbind();
	quadVAO.Unbind();
	auto fbo = std::make_unique<Pesto::FrameBuffer>(window.GetWindowWidth(), window.GetWindowHeight(), hdrOn);
	//Pesto::FrameBuffer fbo{window.GetWindowWidth(), window.GetWindowHeight(), hdrOn};


	vao.Bind();
#endif

	Pesto::VertexBuffer instanceVbo;
	instanceVbo.Bind();
	glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(GeoMa::Vector3F), 0);

	glVertexAttribDivisor(1,1);

	particleSystem.setEmitterPosition(GeoMa::Vector3F(0.0f, 0.0f, 0.0f));
	glEnable(GL_PROGRAM_POINT_SIZE);

	Pesto::VertexBuffer sizeVBO;
	sizeVBO.Bind();
	glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), static_cast<void *>(nullptr));
	glVertexAttribDivisor(2, 1);


	Pesto::VertexBuffer lifeVBO;
	lifeVBO.Bind();
	glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), static_cast<void *>(nullptr));
	glVertexAttribDivisor(3, 1);

	//lifetimes

	vao.Unbind();

	osc.startListening(3333);


    //shaders & cubemap
	Pesto::Shader shader{(SHADERS_PATH + "basic.vert").c_str(), (SHADERS_PATH + "basic.frag").c_str()};
	Pesto::Shader screenShader{(SHADERS_PATH + "screen.vert").c_str(), (SHADERS_PATH + "screen.frag").c_str()};
	Pesto::Shader cubemapShader{(SHADERS_PATH + "skybox.vert").c_str(), (SHADERS_PATH + "skybox.frag").c_str()};

	Pesto::CubeMap cubemap;
	cubemap.Init();

	initUI(window.GetWindowAddr());

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.GetWindowAddr())) {
		Pesto::Time::Update();
		Pesto::InputManager::Update();

		ApplyOSC(); // applique les parametres envoyés depuis le hand tracking et pesto

		//ImGui::ShowDemoWindow();
		// input
		// -----
		// std::cout << "Before input" << std::endl;
		if(Pesto::InputManager::IsKeyDown(Pesto::Key::LCTRL))
			camera.ProcessMouseInputs();

		if (Pesto::InputManager::IsKeyPressed(Pesto::Key::R))
			particleSystem.resetAllParticles();

		camera.ProcessKeyboardInputs();
		ProcessInput();

		fbo->Bind();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f,114.0f/255.0f,229.0f/255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render
		// ------
		particleSystem.update(Pesto::Time::GetDeltaTime());

		// update l'instancing
		instanceVbo.Bind();

		// Le cpu transfere directement les données dans une place libre du GPU
		//positions
		glBufferData(GL_ARRAY_BUFFER, particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, particleSystem.getParticlesCount() * sizeof(GeoMa::Vector3F), particleSystem.getPositions().data());
		//sizes
		sizeVBO.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, particleSystem.getParticlesCount() * sizeof(float),
			particleSystem.getSizes().data());
		//lifetimes
		lifeVBO.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, particleSystem.getParticlesCount() * sizeof(float),
			particleSystem.getLifetimes().data());
		lifeVBO.Bind();


		shader.EnableShader();
		shader.SetUniformMat4("camMatrix", camera.CalculateMatrix(0.1, 300));
		GeoMa::Vector3F lightPos = attractorPosition;
		lightPos.z = zDepthLight;
		shader.SetUniform3f("lightPos", lightPos);

		particleSystem.render(shader);
		vao.Bind();
#ifdef DRAW_QUADS
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, particleSystem.getParticlesCount());
#endif

		if (shouldDrawCubeMap)
			cubemap.Draw(cubemapShader, GeoMa::Matrix4F(camera.GetViewMatrix(), true), GeoMa::Matrix4F(camera.GetProjectionMatrix(0.1, 300.0), true));

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// drawing particles
		screenShader.EnableShader();
		screenShader.SetUniform1f("gamma", gammaValue);
		screenShader.SetUniform1i("hdrEnabled", hdrOn);
		screenShader.SetUniform1f("exposure", exposureValue);
		quadVAO.Bind();
		fbo->BindTexture();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		screenShader.DisableShader();

		// imgui
		DrawUI(fbo);
		glfwSwapBuffers(window.GetWindowAddr());
		glfwPollEvents();

		window.AddFpsTitle(std::to_string((u32)Pesto::Time::GetFPS()));
	}
}

void Application::Destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Application::ApplyOSC() {
	if (shouldUsePesto) {
		float _clampedAttractionForce = std::clamp(static_cast<float>(attractionForce), 0.0f, 100.0f);
		particleSystem.setAttractionForce(_clampedAttractionForce);
	} else {
		particleSystem.setAttractionForce(attractionForce);
	}

	if (shouldUseOscValues) {
		particleSystem.setAttractionRadius(osc._radius);
		GeoMa::Vector3F posFromOsc;
		posFromOsc.x = (osc._attractorX * 80.0f) - 40.0f;
		posFromOsc.y = (osc._attractorY * 60.0f) - 30.0f;
		posFromOsc.z = 0.0f;
		particleSystem.setAttractionPosition(posFromOsc);
	} else {
		particleSystem.setAttractionRadius(attractionRadius);
		particleSystem.setAttractionPosition(attractorPosition);
	}
}

void Application::ProcessInput() {
	if (Pesto::InputManager::IsKeyPressed(Pesto::ESCAPE)) {
		glfwSetWindowShouldClose(window.GetWindowAddr(), true);
	}
	if (Pesto::InputManager::IsKeyPressed(Pesto::Key::TAB)) {
		drawImgui = !drawImgui;
	}
}

void Application::DrawUI(std::unique_ptr<Pesto::FrameBuffer>& fbo) {
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
	if (ImGui::CollapsingHeader("Cubemap")) {
		ImGui::Checkbox("Draw Cubemap", &shouldDrawCubeMap);
	}
	if (ImGui::CollapsingHeader("Forces")) {
		ImGui::SliderFloat3("Attraction Position", &attractorPosition.x, -50.f, 50.f);
		ImGui::SliderFloat("Attraction Force", &attractionForce, 0.f, 100.f);
		ImGui::SliderFloat("Attraction Radius", &attractionRadius, 0.f, 250.f);
	}
	if (ImGui::CollapsingHeader("OSC")) {
		ImGui::Checkbox("Use OSC", &shouldUseOscValues);
	}
	if (ImGui::CollapsingHeader("Z light depth")) {
		ImGui::SliderFloat("Z light pos", &zDepthLight, -50.0f, 50.0f);
	}
	if (ImGui::CollapsingHeader("Use PESTO")) {
		ImGui::Checkbox("Use Pesto", &shouldUsePesto);
	}
	if (ImGui::CollapsingHeader("Use HDR")) {
		if (ImGui::Checkbox("HDR", &hdrOn)) {
			fbo = std::make_unique<Pesto::FrameBuffer>(window.GetWindowWidth(), window.GetWindowHeight(), hdrOn);
		}
		if (ImGui::CollapsingHeader("Postprocessing values")) {
			ImGui::SliderFloat("Gamma value", &gammaValue, 0.0f, 10.0f);
			ImGui::SliderFloat("Exposure value", &exposureValue, 0.0f, 10.0f);
		}
	}
	ImGui::End();
	ImGui::Render();
	if (drawImgui)
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


