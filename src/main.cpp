#include <iostream>

#include "core/Window.h"
#include "core/InputManager.h"

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	Pesto::Window window;

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.GetWindowAddr())) {
		// input
		// -----
		processInput(window.GetWindowAddr());

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window.GetWindowAddr());
		glfwPollEvents();
	}
	return 0;
}

void processInput(GLFWwindow *window) {
	if (Pesto::InputManager::IsKeyPressed(Pesto::ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
}
