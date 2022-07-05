//
// Created by pc on 11-12-21.
//

#ifndef _DISC_H
#define _DISC_H

#include "Identifier.h"
#include "Material.h"

#include <glm/vec3.hpp>

namespace trace {
    class Ray;

    struct Disc : public Identifier {
        Disc(float _radius, const glm::vec3& _center, const glm::vec3& _normal, const Material& _material);

        [[nodiscard]] float distance(const Ray& _ray) const;

        float     radius;
        float     dotNormalCenter;
        glm::vec3 center;
        glm::vec3 normal;
        Material  material;
    };
} // namespace trace

#endif // _DISC_H
