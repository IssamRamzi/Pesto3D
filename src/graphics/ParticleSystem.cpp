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

    void ParticleSystem::resetParticle(std::size_t idx){
        if(idx > _mParticles.size()){
            std::cout << "reset particle : overflow idx" << std::endl;
            return;
        }

        Particle& p = _mParticles[idx];
        float velx = ((float)rand() / (float)RAND_MAX - 0.5f) * 2.0f;
        float vely = (float)rand() / (float)RAND_MAX * SPEED;

       p.position = _position + GeoMa::Vector3F(
            ((float)rand() / (float)RAND_MAX - 0.5f) * 100.f,
            0.0f, 
            0.0f
        );
        p.velocity = GeoMa::Vector3F(velx, vely, 0.0f);
        p.size = _particleSize;
        p.lifetime = rand() % 1800 + 1800; // 0.5s > life > 1s  (pas sur)
        p.isDead = false;
    }

    void ParticleSystem::update(f32 delta){
        for(size_t i = 0; i < _mParticles.size(); i++){
            Particle& p = _mParticles[i];
            GeoMa::Matrix4F modelMatrix = GeoMa::Matrix4F::Scale(p.size, {1,1,1});

            if(!p.isDead){
                p.velocity.y -= 9.8 * delta * 0.1;
                p.position.x += p.velocity.x * delta;
                p.position.y += p.velocity.y * delta;
                p.position.z += p.velocity.z * delta;

                // TODO: process lifetime
                if(p.lifetime < 0){
                    resetParticle(i);
                }

                // pour le batching
                _positions[i] = p.position;
                _sizes[i] = p.size;
            }
        }
    }
} 
