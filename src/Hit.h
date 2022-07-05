//
// Created by pc on 11-12-21.
//

#ifndef _HIT_H
#define _HIT_H

#include "Material.h"
#include "Types.h"

#include <glm/vec3.hpp>

namespace trace {

    struct Hit {

        size_t    identifier = std::numeric_limits<size_t>::max();
        float     distance   = std::numeric_limits<float>::max();
        OBJECT_TYPE type;
        Material  material;
        glm::vec3 intersectionPoint;
        glm::vec3 outwardNormal;
        glm::vec3 inwardDirection;

        bool operator<(const Hit& other) const;
    };
} // namespace trace

#endif // _HIT_H
