#include "HitableList.h"

#include <iostream>

#include "Sphere.h"

namespace dc {

HitableList::~HitableList() {
    for (auto h : m_list)
        delete h;
}

void HitableList::append(const Hitable * hitable) {
    m_list.push_back(hitable);
}

HitableList::HitRecord HitableList::hit(const ray & r, const float t_min, const float t_max) const {
    HitRecord retRec;
    HitRecord tmpRec;
    float closestSoFar = t_max;
    for (auto h : m_list) {
        tmpRec = h->hit(r, t_min, closestSoFar);
        if (tmpRec.t > 0.f)
        {
            retRec.t = tmpRec.t;
            retRec.P = tmpRec.P;
            retRec.N = tmpRec.N;
            closestSoFar = retRec.t;
        }
    }

    return retRec;
}

} // dc