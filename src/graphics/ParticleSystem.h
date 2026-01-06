#pragma once
#include "../math/Vector3.h"
#include "../globals.h"
#include <vector>


namespace Pesto {
    #define MAX_PARTICLES 1000000

    class ParticleSystem
    {
        struct Particle
        {
            GeoMa::Vector3F position;
            GeoMa::Vector3F velocity;
            int lifetime = 5.0f;
            float size = 1.0f;
            bool isDead = false;
        };

    public:
        ParticleSystem(GeoMa::Vector3F position = GeoMa::Vector3F::ZERO);
        void resetParticle(std::size_t idx);
        void update(f32 delta);
        void render();

        


        void setEmitterPosition(GeoMa::Vector3F newPosition){ _position = newPosition; }


        u16 getParticlesCount()const{return MAX_PARTICLES;}
        // les getters pour l'instancing

        std::vector<GeoMa::Vector3F>& getPositions() {return _positions;}
        std::vector<GeoMa::Vector3F>& getSizes() {return _sizes;}

    private:
    
        std::vector<Particle> _mParticles;
        GeoMa::Vector3F _position;
    
        float _particleSize = 5.0f;

        // pour l'instancing
        std::vector<GeoMa::Vector3F> _positions;
        std::vector<GeoMa::Vector3F> _sizes;

    };
}
