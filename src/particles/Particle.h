//
// Created by Issam on 15/01/2026.
//

#ifndef PESTO3D_PARTICLE_H
#define PESTO3D_PARTICLE_H
#include "../math/GeoMa.h"

namespace Pesto{
    struct Particle
    {
        GeoMa::Vector3F position;
        GeoMa::Vector3F velocity;
        float lifetime = 10.0f;
        float size = .05f;
        bool isDead = false;
    };
}
#endif //PESTO3D_PARTICLE_H