#include "Sphere.h"

namespace dc
{

bool Sphere::hit(const ray & r, const float t_min, const float t_max, HitRecord & record) const {
    v3f oc = r.origin() - m_center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - m_radius * m_radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0.f) {
        float t1 = (-b - sqrtf(discriminant)) / a;
        float t2 = (-b + sqrtf(discriminant)) / a;
        float t = -1.f;;
        if (t1 > t_min && t1 < t_max)
            t = t1;
        else if (t2 > t_min && t2 < t_max)
            t = t2;

        if (t > 0.f) {
            record.P = r.pointAtParameter(t);
            record.N = (record.P - m_center) / m_radius;
            record.t = t;
            return true;
        }
    }

    return false;
}

} // dc