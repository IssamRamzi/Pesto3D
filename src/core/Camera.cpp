#include "Camera.h"
#include <iostream>
#include "InputManager.h"

namespace Pesto
{
    

using namespace GeoMa;

Camera::Camera(Window* window, Vector3F position) {
    m_position = position;
    m_initialPosition = position;
    m_window = window;
    last_mousePos = InputManager::GetMousePosition();
}

Camera::~Camera() {
    // Destructor
}

Matrix4F Camera::CalculateMatrix(float nearPlane, float farPlane) {
    Matrix4F view = Matrix4F::LookAt(m_position, m_position + m_orientation, m_up);

    float aspect = (float)m_window->GetWindowWidth() / (float)m_window->GetWindowHeight();
    
    Matrix4F projection = Matrix4F::Perspective(
        (double)ToRadians(m_fov), 
        (double)aspect, 
        (double)nearPlane, 
        (double)farPlane
    );

    
    return projection * view;// TOUJOURS PROJ * VIEW
}

void Camera::ProcessKeyboardInputs() {
    if (InputManager::IsKeyDown(LSHIFT)) {
        m_speed = m_initialSpeed * 3.0;
    } else {
        m_speed = m_initialSpeed;
    }

    if (InputManager::IsKeyPressed(SPACE)) {
        m_orientation = Vector3F(0.0, 0.0, -1.0);
        m_position = m_initialPosition;
    }

    if (InputManager::IsKeyDown(Z)) {
        std::cout << "Pressing Z"<<std::endl;
        m_position = m_position + (m_orientation * m_speed);
    }
    if (InputManager::IsKeyDown(S)) {
        m_position = m_position - (m_orientation * m_speed);
    }
    if (InputManager::IsKeyDown(Q)) {
        m_position = m_position - (m_right * m_speed);
    }
    if (InputManager::IsKeyDown(D)) {
        m_position = m_position + (m_right * m_speed);
    }
    if (InputManager::IsKeyDown(A)) {
        m_position = m_position + (m_up * m_speed);
    }
    if (InputManager::IsKeyDown(E)) {
        m_position = m_position - (m_up * m_speed);
    }
}

void Camera::ProcessMouseInputs() {
    auto mouseDelta = InputManager::GetMouseDelta();

    yaw   += mouseDelta.x * m_sensitivity;
    pitch -= mouseDelta.y * m_sensitivity;

    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    Vector3F front;
    front.x = cos(ToRadians(yaw)) * cos(ToRadians(pitch));
    front.y = sin(ToRadians(pitch));
    front.z = sin(ToRadians(yaw)) * cos(ToRadians(pitch));
    
    m_orientation = front.Normalized();

    m_right = Vector3<float>::Cross(m_orientation, Vector3F::UP).Normalized();
    m_up    = Vector3<float>::Cross(m_right, m_orientation).Normalized();
}

void Camera::ProcessMouseScroll() {
}

} // namespace Pesto
