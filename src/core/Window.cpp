//
// Created by Issam on 30/12/2025.
//

#include "Window.h"

#include <iostream>


namespace Pesto{

void resize_callback(GLFWwindow * window, int width, int height) {
    Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);
    currentWindow->SetWindowDimensions(width, height);
    glViewport(0, 0, width, height);
}

Window::Window() {
    Init();
}

Window::Window(WindowSettings settings) : m_Settings(settings) {
    Init();
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}



void Window::Init() {
    if (!glfwInit()) {
        std::cout << "Window constructor : Failed to init glfw\n";
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(m_Settings.Width, m_Settings.Height, m_Settings.Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        std::cout << "Window constructor : Failed to create window\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_Window);

    // TODO: set callbacks
    glfwSetFramebufferSizeCallback(m_Window, resize_callback);
    glfwSetWindowUserPointer(m_Window, this);

    if (!gladLoadGL()) {
        std::cout << "Window constructor : Failed to load opengl\n";
        glfwTerminate();
        return;
    }
}


}
