#pragma once

#include <vector>

#include "Hitable.h"

namespace dc {

class HitableList : public Hitable {
public:
    HitableList() {}
    ~HitableList(); // WARNING: HitableList is responsible for hitable objects it contains. The destructor will delete them
    void append(const Hitable * hitable);
    virtual HitRecord hit(const ray & r, const float t_min, const float t_max) const override;

private:
    std::vector<const Hitable *> m_list;
};

} // dc