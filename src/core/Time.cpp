//
// Created by Issam on 30/12/2025.
//

#include "Time.h"
#include <GLFW/glfw3.h>

namespace Pesto{
    float Time::m_fps = 0.0f;
    int   Time::m_numFrames = 0;

    float Time::m_deltaTime = 0.0f;
    float Time::m_lastFrameTime = 0.0f;
    float Time::m_fpsTimer = 0.0f;

    void Time::Init()
    {
        m_lastFrameTime = glfwGetTime();
        m_fpsTimer = m_lastFrameTime;
        m_numFrames = 0;
        m_fps = 0.0f;
    }

    void Time::Update()
    {
        double currentTime = glfwGetTime();

        m_deltaTime = static_cast<float>(currentTime - m_lastFrameTime);
        m_lastFrameTime = static_cast<float>(currentTime);

        m_numFrames++;

        if (currentTime - m_fpsTimer >= 1.0)
        {
            m_fps = static_cast<float>(m_numFrames);
            m_numFrames = 0;
            m_fpsTimer += 1.0f;
        }
    }
}