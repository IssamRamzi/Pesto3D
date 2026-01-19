#include "Particle.h"

namespace Pesto{
    class ForceManager{
    public:
        ForceManager() = default;

        // attraction
        void setAttractorPosition(GeoMa::Vector3F position){_attractionPosition = position;}
        void setAttractorForce(float force){_attractionForce = force;}
        void setAttractorRadius(float radius){_attractionRadius = radius;}
        void attract(Pesto::Particle& p, float dt);
        //friction
        void doFriction(Particle& p, float force);


    private:
        GeoMa::Vector3F _attractionPosition = GeoMa::Vector3F::ZERO;
        float _attractionForce = 20.0f;
        float _attractionRadius = 30.0f;
    };
}