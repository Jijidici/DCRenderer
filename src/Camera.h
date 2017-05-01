#pragma once

#include "ray.h"

namespace dc {

class Camera {
public:
    Camera()
        : origin(0.f)
        , lowerLefCorner(-2.f, -1.f, -1.f)
        , horizontal(4.f, 0.f, 0.f)
        , vertical(0.f, 2.f, 0.f)
    {}

    ray getRay(float u, float v) {
        return ray(origin, lowerLefCorner + u * horizontal + v * vertical - origin);
    }

    v3f origin;
    v3f lowerLefCorner;
    v3f horizontal;
    v3f vertical;
};

} // dc