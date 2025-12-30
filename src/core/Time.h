//
// Created by Issam on 30/12/2025.
//

#ifndef PESTO3D_TIME_H
#define PESTO3D_TIME_H

namespace Pesto {
    class Time {
    private:
        static float m_fps;
        static int   m_numFrames;

        static float m_deltaTime;
        static float m_lastFrameTime;
        static float m_fpsTimer;

    public:
        static void Init();
        static void Update();

        static float GetDeltaTime() { return m_deltaTime; }
        static float GetFPS()       { return m_fps; }
    };
}

#endif //PESTO3D_TIME_H