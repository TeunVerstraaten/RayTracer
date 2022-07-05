//
// Created by pc on 11-12-21.
//

#include "Hit.h"

namespace trace {

    bool Hit::operator<(const Hit& other) const {
        return other.distance > distance;
    }
} // namespace trace