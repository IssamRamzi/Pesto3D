#include "ParticleSystem.h"

#include <random>

#define SPEED 5.0f

namespace Pesto
{
    ParticleSystem::ParticleSystem(GeoMa::Vector3F position, ForceManager attractor) : _position(position){
        _mParticles.resize(MAX_PARTICLES);
        _positions.resize(MAX_PARTICLES);
        _sizes.resize(MAX_PARTICLES);
        for(int i = 0 ; i < MAX_PARTICLES; i++){
            resetParticle(i);
        }
        _attractor = attractor;
    }

    void ParticleSystem::resetAllParticles()
    {
        for(int i = 0 ; i < MAX_PARTICLES; i++){
            resetParticle(i);
        }
    }

    void ParticleSystem::setEmitterPosition(GeoMa::Vector3F newPosition)
    {
        _position = newPosition;
    }


    void ParticleSystem::resetParticle(std::size_t idx){
        if(idx > _mParticles.size()){
            std::cout << "reset particle : overflow idx" << std::endl;
            return;
        }

        Particle& p = _mParticles[idx];
        float velx = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) * 2.0f;
        float vely = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * SPEED;

       p.position = _position + GeoMa::Vector3F(
            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) * 100.f,
            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) * 5.f,
            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) * 10.f
        );
        p.velocity = GeoMa::Vector3F(velx, vely, 0.0f);
        p.lifetime = 2.0f;
        p.isDead = false;
    }



        void ParticleSystem::update(f32 delta){
            for (size_t i = 0; i < _mParticles.size(); i++) {
                Particle& p = _mParticles[i];
                if (p.isDead) continue;

                _attractor.attract(p, delta);
                //
                _attractor.doFriction(p, 0.98);

                // gravity
                p.velocity.y -= 9.8f * delta * 0.1f;

                p.position = p.position + p.velocity * delta;

                p.lifetime -= delta;
                // if (p.lifetime <= 0.0f)
                    // resetParticle(i);

                _positions[i] = p.position;
                _sizes[i] = p.size;
            }
        }

    void ParticleSystem::render(Shader& shader) {
        for(size_t i = 0; i < _mParticles.size(); i++) {
            Particle& p = _mParticles[i];
            // shader.SetUniform1f("l", p.lifetime); // one uniform call costs 70 to 120 fps
            shader.SetUniform1f("particleSize", p.size);
        }
    }
}
