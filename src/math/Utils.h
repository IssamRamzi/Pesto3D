#pragma once

#ifndef UTILS_H
#define UTILS_H

namespace GeoMa{

    #define PI 3.1415926535

    inline double ToRadians(float degrees){
        return degrees * PI / 180;
    }
}

#endif // UTILS_H