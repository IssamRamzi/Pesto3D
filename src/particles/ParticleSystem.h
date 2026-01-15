#pragma once
#include "../math/Vector3.h"
#include "../globals.h"
#include <vector>

#include "../graphics/Shader.h"


namespace Pesto {
#define MAX_PARTICLES 1000000

    class ParticleSystem
    {
        struct Particle
        {
            GeoMa::Vector3F position;
            GeoMa::Vector3F velocity;
            float lifetime = 5.0f;
            float size = 0.2f;
            bool isDead = false;
        };



    public:
        ParticleSystem(GeoMa::Vector3F position = GeoMa::Vector3F::ZERO);
        void resetParticle(std::size_t idx);
        void update(f32 delta);
        void render(Shader& shader);
        void resetAllParticles();
        //void setLifeTime(float lifetime = 1.0f, size_t idx);

        void setEmitterPosition(GeoMa::Vector3F newPosition);

        u32 getParticlesCount()const{return MAX_PARTICLES;}
        // les getters pour l'instancing

        std::vector<GeoMa::Vector3F>& getPositions() {return _positions;}
        std::vector<GeoMa::Vector3F>& getSizes() {return _sizes;}

    private:

        std::vector<Particle> _mParticles;
        GeoMa::Vector3F _position;

        // pour l'instancing
        std::vector<GeoMa::Vector3F> _positions;
        std::vector<GeoMa::Vector3F> _sizes;

    };
}
