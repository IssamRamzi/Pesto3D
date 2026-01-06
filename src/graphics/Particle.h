#pragma once
#include "../math/Vector3.h"

namespace Pesto {
    class ParticleSystem
    {
        struct Particle
        {
            GeoMa::Vector3<float> velocity;
            int lifetime = 0;
        };

    public:
        ParticleSystem();
        void resetParticle(std::size_t idx);

    private:
        std::vector<Particle> _mParticles;
        GeoMa::Vector3<float> _position;
        float _particleSize = 8.0f;

    };
}
