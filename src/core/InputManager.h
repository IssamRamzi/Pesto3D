//
// Created by Issam on 30/12/2025.
//

#ifndef PESTO3D_INPUTMANAGER_H
#define PESTO3D_INPUTMANAGER_H

#include <map>
#include <vector>

#include "../globals.h"
#include "Window.h"
#include "../math/GeoMa.h"


namespace Pesto{
    using namespace GeoMa;
    enum Key{
        UP, DOWN, LEFT, RIGHT, SPACE, ENTER, ESCAPE, LCTRL, RCTRL, LSHIFT, RSHIFT, TAB,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y , Z, KeysCount};
    enum MouseButton{BUTTON_LEFT, BUTTON_RIGHT, BUTTON_MIDDLE, MouseCount};

    class InputManager {
    private:
        static GLFWwindow* m_window;
        static std::vector<bool> keysPressed;
        static std::vector<bool> lastKeysPressed;
        static std::vector<bool> mousePressed;
        static std::map<int, Key> keyMap;
        static std::map<int, MouseButton> mouseMap;

        static double prevMouseX, currentMouseX, prevMouseY, currentMouseY;

    private:
        InputManager() = delete;
        ~InputManager() = delete;

    public:
        static void Init(GLFWwindow* _window);

        static void Update();

        static bool IsKeyDown(Key key);
        static bool IsKeyPressed(Key key);
        static bool IsMouseClicked(MouseButton button);

        static Vector2F GetMousePosition();
        static Vector2F GetMouseDelta();
    };
}

#endif //PESTO3D_INPUTMANAGER_H