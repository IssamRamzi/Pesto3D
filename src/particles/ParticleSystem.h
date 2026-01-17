#pragma once
#include "../math/Vector3.h"
#include "../globals.h"
#include <vector>

#include "ForceManager.h"
#include "../graphics/Shader.h"
#include "Particle.h"

namespace Pesto {
    #define MAX_PARTICLES 200000




    class ParticleSystem
    {


    public:
        ParticleSystem(GeoMa::Vector3F position = GeoMa::Vector3F::ZERO, ForceManager attractor = ForceManager());
        void resetParticle(std::size_t idx);
        void update(f32 delta);
        void render(Shader& shader);
        void resetAllParticles();
        //void setLifeTime(float lifetime = 1.0f, size_t idx);

        void setEmitterPosition(GeoMa::Vector3F newPosition);
        void setAttractionForce(float attractionForce){_attractor.setAttractorForce(attractionForce);}
        void setAttractionRadius(float attractionRadius){_attractor.setAttractorRadius(attractionRadius);}
        void setAttractionPosition(GeoMa::Vector3F attractionPosition){_attractor.setAttractorPosition(attractionPosition);}

        u32 getParticlesCount()const{return MAX_PARTICLES;}

        void attract(size_t idx, float dt);

        // les getters pour l'instancing

        std::vector<GeoMa::Vector3F>& getPositions() {return _positions;}
        std::vector<GeoMa::Vector3F>& getSizes() {return _sizes;}


    private:
    
        std::vector<Particle> _mParticles;
        GeoMa::Vector3F _position;
    
        // pour l'instancing
        std::vector<GeoMa::Vector3F> _positions;
        std::vector<GeoMa::Vector3F> _sizes;

        ForceManager _attractor;



    };
}
