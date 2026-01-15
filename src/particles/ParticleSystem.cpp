#include "ParticleSystem.h"

#include <random>

#define SPEED 5.0f

namespace Pesto
{
    ParticleSystem::ParticleSystem(GeoMa::Vector3F position) : _position(position){
        _mParticles.resize(MAX_PARTICLES);
        _positions.resize(MAX_PARTICLES);
        _sizes.resize(MAX_PARTICLES);

        for(int i = 0 ; i < MAX_PARTICLES; i++){
            resetParticle(i);
        }
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
            0.0f, 
            0.0f
        );
        p.velocity = GeoMa::Vector3F(velx, vely, 0.0f);
        p.lifetime = 1.0f; // 0.5s > life > 1s
        p.isDead = false;
    }



        void ParticleSystem::update(f32 delta){
            for(size_t i = 0; i < _mParticles.size(); i++){
                Particle& p = _mParticles[i];

                if(!p.isDead){
                    p.velocity.y -= 9.8 * delta * 0.1;
                    p.position.x += p.velocity.x * delta;
                    p.position.y += p.velocity.y * delta;
                    p.position.z += p.velocity.z * delta;

                    // TODO: process lifetime
                    p.lifetime -= delta;
                    if (p.lifetime < 0) {
                        resetParticle(i);
                    }

                    // pour le batching
                    _positions[i] = p.position;
                    _sizes[i] = p.size;
                }
            }
        }

    void ParticleSystem::render(Shader& shader) {
        for(size_t i = 0; i < _mParticles.size(); i++) {
            Particle& p = _mParticles[i];
            shader.SetUniform1f("l", p.lifetime);
        }
    }
}
