//
// Created by Issam on 30/12/2025.
//

#ifndef PESTO3D_WINDOW_H
#define PESTO3D_WINDOW_H

#include <string>


#include "../globals.h"
#include "../math/GeoMa.h"
#include "glad.h"
#include "GLFW/glfw3.h"

namespace Pesto{
class Window {
    typedef struct {
        u16 Width {1600};
        u16 Height {900};
        std::string Title{"Pesto3D"};
    } WindowSettings;
public:
    Window();
    Window(WindowSettings settings);
    ~Window();

    inline WindowSettings GetSettings() {return m_Settings;}
    inline GLFWwindow* GetWindowAddr() {return m_Window;}
    inline void SetWindowDimensions(int width, int height){m_Settings.Width = width, m_Settings.Height = height;}

    void AddFpsTitle(std::string title){ glfwSetWindowTitle(m_Window, (m_Settings.Title + " - FPS " + title).c_str());}
    f32 GetWindowWidth(){return m_Settings.Width;}
    f32 GetWindowHeight(){return m_Settings.Height;}
    void SetVsync(bool state){glfwSwapInterval(state);}

private:
    WindowSettings m_Settings;
    GLFWwindow* m_Window;

private:
    void Init();


};
}

#endif //PESTO3D_WINDOW_H