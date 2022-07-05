//
// Created by pc on 11-12-21.
//

#ifndef _PLANE_H
#define _PLANE_H

#include "Identifier.h"
#include "Material.h"

#include <glm/vec3.hpp>

namespace trace {

    struct Ray;
    struct Scene;

    struct Plane : public Identifier {
        Plane(const glm::vec3& _point, const glm::vec3& _normal, const Material& _material);

        [[nodiscard]] float distance(const Ray& _ray) const;

        float     dotNormalPoint;
        glm::vec3 normal;
        Material  material;
    };
} // namespace trace

#endif // _PLANE_H
