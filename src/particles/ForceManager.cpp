//
// Created by Issam on 15/01/2026.
//

#include "ForceManager.h"

namespace Pesto {
    // https://github.com/codemaker4/raylib-particle-toy/blob/master/particle.h
    void ForceManager::attract(Particle &p, float dt) {

        GeoMa::Vector3F toAttractor = _attractionPosition - p.position;
        float distance = toAttractor.Length();
        GeoMa::Vector3F dir = toAttractor.Normalized();

        if (distance < _attractionRadius) {
            const float force = _attractionForce * (1.0f - distance / _attractionRadius);
            p.velocity = p.velocity + dir * force * dt;
        }
    }

    void ForceManager::doFriction(Particle& p, float force) {
        p.velocity.x *= force;
        p.velocity.y *= force;
    }
}
