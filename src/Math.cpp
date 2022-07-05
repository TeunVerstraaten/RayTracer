//
// Created by pc on 11-12-21.
//

#include "Math.h"

#include <cstdlib>
#include <glm/geometric.hpp>

namespace trace::math {
    float random_double() {
        return rand() / (static_cast<float>(RAND_MAX) + 1.0f);
    }
    float random_double(float _min, float _max) {
        // Returns a randomVec3 real in [_min,_max).
        return _min + (_max - _min) * random_double();
    }

    glm::vec3 randomVec3(float _min, float _max) {
        return {random_double(_min, _max), random_double(_min, _max), random_double(_min, _max)};
    }

    glm::vec3 randomOnUnitSphere() {
        // Rejection sampling of point on unit sphere: Sample until you get point IN the sphere, then normalize its length
        while (true) {
            auto p = randomVec3(-1, 1);
            auto l = glm::length(p);
            if (l >= 1.0f)
                continue;

            return p / l;
        }
    }
} // namespace trace::math