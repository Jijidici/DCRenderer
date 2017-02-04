#pragma once

#include "../ray.h";

namespace dc
{

class Hitable {
public:

    struct HitRecord {
        HitRecord() : t(-1.f), P(v3f(0.f)), N(v3f(0.f)) {}

        float t;
        v3f P;
        v3f N;
    };

    virtual HitRecord hit(const ray & r, const float t_min, const float t_max) const = 0;
};

} // dc