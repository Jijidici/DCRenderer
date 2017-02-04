#pragma once

#include "vec3.h"

namespace dc
{

class ray {
public:
    ray() { m_o = v3f(0.f); m_d = v3f(0.f); }
    ray(const v3f & o, const v3f & d) { m_o = o; m_d = normalize(d); }
    v3f origin() const { return m_o; }
    v3f direction() const { return m_d; }
    v3f pointAtParameter(float t) const { return m_o + t * m_d; }

private:
    v3f m_o;
    v3f m_d;
};

} // dc