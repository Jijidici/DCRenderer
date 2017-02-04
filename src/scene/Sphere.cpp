#include "Sphere.h"

namespace dc
{

Sphere::HitRecord Sphere::hit(const ray & r, const float t_min, const float t_max) const {
    HitRecord retRec;
    v3f oc = r.origin() - m_center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - m_radius * m_radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0.f) {
        float t1 = (-b - sqrtf(discriminant)) / a;
        float t2 = (-b + sqrtf(discriminant)) / a;
        if (t1 > t_min && t1 < t_max)
            retRec.t = t1;
        else if (t2 > t_min && t2 < t_max)
            retRec.t = t2;

        if (retRec.t > 0.f) {
            retRec.P = r.pointAtParameter(retRec.t);
            retRec.N = (retRec.P - m_center) / m_radius;
        }
    }

    return retRec;
}

} // dc