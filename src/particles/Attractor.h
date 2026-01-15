//
// Created by Issam on 09/01/2026.
//

#ifndef PESTO3D_ATTRACTOR_H
#define PESTO3D_ATTRACTOR_H
#include <vector>

#include "../math/GeoMa.h"


class Attractor {
public:



private:
    GeoMa::Vector2F _attractorPosition;
    float _attractionFactor;

    std::vector<GeoMa::Vector2F> _particlesPositions;

};


#endif //PESTO3D_ATTRACTOR_H

