#pragma once

#include "vec3.h"

namespace dc
{

class ray {
public :
    ray() { A = v3f(0.f); B = v3f(0.f); }
    ray(const v3f& a, const v3f& b) { A = a; B = normalize(b); }
    v3f origin() const { return A; }
    v3f direction() const { return B; }
    v3f pointAtParameter(float t) const { return A + t*B; }

    v3f A;
    v3f B;
};

} // dc