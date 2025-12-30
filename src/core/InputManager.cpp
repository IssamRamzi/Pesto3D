//
// Created by Issam on 30/12/2025.
//

#include "InputManager.h"

namespace Pesto{

std::map<int, Key> InputManager::keyMap = {
    {GLFW_KEY_UP, UP},
    {GLFW_KEY_DOWN, DOWN},
    {GLFW_KEY_LEFT, LEFT},
    {GLFW_KEY_RIGHT, RIGHT},
    {GLFW_KEY_SPACE, SPACE},
    {GLFW_KEY_ENTER, ENTER},
    {GLFW_KEY_ESCAPE, ESCAPE},
    {GLFW_KEY_LEFT_CONTROL, LCTRL},
    {GLFW_KEY_RIGHT_CONTROL, RCTRL},
    {GLFW_KEY_LEFT_SHIFT, LSHIFT},
    {GLFW_KEY_RIGHT_SHIFT, RSHIFT},
    {GLFW_KEY_TAB, TAB},
    {GLFW_KEY_A, Q},
    {GLFW_KEY_B, B},
    {GLFW_KEY_C, C},
    {GLFW_KEY_D, D},
    {GLFW_KEY_E, E},
    {GLFW_KEY_F, F},
    {GLFW_KEY_G, G},
    {GLFW_KEY_H, H},
    {GLFW_KEY_I, I},
    {GLFW_KEY_J, J},
    {GLFW_KEY_K, K},
    {GLFW_KEY_L, L},
    {GLFW_KEY_M, M},
    {GLFW_KEY_N, N},
    {GLFW_KEY_O, O},
    {GLFW_KEY_P, P},
    {GLFW_KEY_Q, A},
    {GLFW_KEY_R, R},
    {GLFW_KEY_S, S},
    {GLFW_KEY_T, T},
    {GLFW_KEY_U, U},
    {GLFW_KEY_V, V},
    {GLFW_KEY_W, Z},
    {GLFW_KEY_X, X},
    {GLFW_KEY_Y, Y},
    {GLFW_KEY_Z, W},
};

std::map<int, MouseButton> InputManager::mouseMap = {
    {GLFW_MOUSE_BUTTON_LEFT, BUTTON_LEFT},
    {GLFW_MOUSE_BUTTON_RIGHT, BUTTON_RIGHT},
    {GLFW_MOUSE_BUTTON_MIDDLE, BUTTON_MIDDLE},
};
std::vector<bool> InputManager::lastKeysPressed(KeysCount, false);
std::vector<bool> InputManager::keysPressed(KeysCount, false);
std::vector<bool> InputManager::mousePressed(MouseCount, false);

double InputManager::prevMouseX = 0.0;
double InputManager::prevMouseY = 0.0;
double InputManager::currentMouseX = 0.0;
double InputManager::currentMouseY = 0.0;

GLFWwindow* InputManager::m_window = nullptr;

void InputManager::Init(GLFWwindow* _window) {
    m_window = _window;

    if(m_window){
        glfwGetCursorPos(m_window, &currentMouseX, &currentMouseY);
        prevMouseX = currentMouseX;
        prevMouseY = currentMouseY;
    }
}

void InputManager::Update() {
    lastKeysPressed = keysPressed;
    for (const std::pair<int, Key> pair : keyMap)
    {
        if (pair.second == Key::KeysCount) break;
        bool keyPressed = glfwGetKey(m_window, pair.first) == GLFW_PRESS;
        keysPressed.at(static_cast<size_t>(pair.second)) = keyPressed;
    }

    for (auto& pair : mouseMap){
        if (pair.second == MouseButton::MouseCount) break;
        bool buttonPressed = glfwGetMouseButton(m_window, pair.first) == GLFW_PRESS;
        mousePressed.at(static_cast<size_t>(pair.second)) = buttonPressed;
    }

    prevMouseX = currentMouseX;
    prevMouseY = currentMouseY;
    glfwGetCursorPos(m_window, &currentMouseX, &currentMouseY);

}

bool InputManager::IsMouseClicked(MouseButton button){
    return mousePressed.at(static_cast<size_t>(button));
}


bool InputManager::IsKeyPressed(Key key) {
    int idx = static_cast<int>(key);
    return keysPressed[idx] && !lastKeysPressed[idx];
}

bool InputManager::IsKeyDown(Key key) {
    return keysPressed.at(static_cast<size_t>(key));
}

Vector2F InputManager::GetMousePosition(){
    return Vector2F{static_cast<float>(currentMouseX),static_cast<float>(currentMouseY)};
}

Vector2F InputManager::GetMouseDelta(){
    float deltaX = currentMouseX - prevMouseX;
    float deltaY = currentMouseY - prevMouseY;
    return {deltaX, deltaY};
}


}

