//
// Created by Issam on 26/01/2026.
//

#ifndef PESTO3D_APPLICATION_H
#define PESTO3D_APPLICATION_H
#include "core/Camera.h"
#include "core/Window.h"
#include "math/GeoMa.h"
#include "particles/ParticleSystem.h"
#include "osc/OscReceiver.h"


class Application {
public:
    Application(){};
    void Initialize();
    void Run();
    void Destroy();

private:


    void DrawUI();
    void ProcessInput();
    void ApplyOSC();

	Pesto::Window window;
    Pesto::Camera camera;
    OscListener osc;

	Pesto::ParticleSystem particleSystem;

    float attractionForce = 20.0f;
    float attractionRadius = 20.0f;
    GeoMa::Vector3F attractorPosition = GeoMa::Vector3F::ZERO;

    bool shouldUseOscValues = false;
    bool shouldDrawCubeMap = false;

    bool drawImgui = false;

};


#endif //PESTO3D_APPLICATION_H