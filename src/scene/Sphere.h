#pragma once

#include "Hitable.h"

namespace dc
{

class Sphere : public Hitable {
public :
    Sphere(v3f center, float radius) : m_center(center), m_radius(radius) {}
    virtual bool hit(const ray & r, const float t_min, const float t_max, HitRecord & record) const override;
    inline v3f center() const { return m_center; }
    inline float radius() const { return m_radius; }

private:
    v3f m_center;
    float m_radius;
};

} // dc