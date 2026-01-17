#include "../math/GeoMa.h"
#include "Window.h"

#pragma once

namespace Pesto{
class Camera
{
public:
    Camera(Window* window, GeoMa::Vector3F position);
    ~Camera();

    GeoMa::Matrix4F   CalculateMatrix(float nearPlane, float farPlane);
    GeoMa::Matrix4F   GetViewMatrix() const;
    GeoMa::Matrix4F   GetProjectionMatrix(float nearPlane, float farPlane) const;

    void              ProcessKeyboardInputs();
    void              ProcessMouseInputs();
    void              ProcessMouseScroll();

    
    GeoMa::Vector3F   GetPosition() const { return m_position; }
    GeoMa::Vector3F   GetUp() const { return m_up; }
    GeoMa::Vector3F   GetOrientation() const { return m_orientation; }
    GeoMa::Vector3F   GetRight() const { return m_right; }
    GeoMa::Vector3F   GetInitialPosition() const { return m_initialPosition; }
    
    float             GetFov() const { return m_fov; }
    float             GetSpeed() const { return m_speed; }

    void              SetFov(float fov) { m_fov = fov; }
    void              SetSpeed(float speed) { m_initialSpeed = speed; }

private:
    Window* m_window;

    GeoMa::Vector3F   m_position;
    GeoMa::Vector3F   m_initialPosition;
    GeoMa::Vector3F   m_orientation = GeoMa::Vector3F(0.0, 0.0, -1.0);
    GeoMa::Vector3F   m_up          = GeoMa::Vector3F(0.0, 1.0, 0.0);
    GeoMa::Vector3F   m_right       = GeoMa::Vector3F(1.0, 0.0, 0.0);
    
    GeoMa::Vector2F   last_mousePos;

    float             m_initialSpeed = 0.05f; 
    float             m_speed        = 0.05f;
    float             m_sensitivity  = 0.1f;
    float             m_fov          = 45.0f;
    
    bool              firstMouse = true;

    // yaw pour rota autour de l'axe des ordonnées (hor)
    // pitch pour rota autour de l'axe des abscisses (ver)
    float             yaw = -90.0f;
    float             pitch = 0.0f;
};
}