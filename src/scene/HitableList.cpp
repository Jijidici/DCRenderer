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

bool HitableList::hit(const ray & r, const float t_min, const float t_max, HitRecord & record) const {
    HitRecord tmpRec;
    bool hitAnything = false;
    float closestSoFar = t_max;
    for (auto h : m_list) {
        if (h->hit(r, t_min, closestSoFar, tmpRec))
        {
            hitAnything = true;
            closestSoFar = tmpRec.t;
            record = tmpRec;
        }
    }

    return hitAnything;
}

} // dc