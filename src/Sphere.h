//
// Created by pc on 11-12-21.
//

#ifndef _SPHERE_H
#define _SPHERE_H

#include "Identifier.h"
#include "Material.h"

#include <glm/vec3.hpp>

namespace trace {

    struct Ray;

    struct Sphere : public Identifier {
        Sphere();
        Sphere(float _radius, const glm::vec3& _center, const Material& _material);
        Sphere(const Sphere& _other);

        [[nodiscard]] float distance(const Ray& _ray) const;

        float     radius = 0;
        glm::vec3 center = {0, 0, 0};
        Material  material{};
    };
} // namespace trace

#endif // _SPHERE_H
