//
// Created by pc on 11-12-21.
//

#include "Plane.h"

#include "Ray.h"

#include <glm/geometric.hpp>

namespace trace {

    Plane::Plane(const glm::vec3& _point, const glm::vec3& _normal, const Material& _material)
        : Identifier(), dotNormalPoint(-glm::dot(_normal, _point)), normal(_normal), material(_material) {
    }

    float Plane::distance(const Ray& _ray) const {
        const auto dotNormalDirection = glm::dot(normal, _ray.direction);
        if (dotNormalDirection == 0)
            return std::numeric_limits<float>::max();

        return -(glm::dot(normal, _ray.start) + dotNormalPoint) / dotNormalDirection;
    }
} // namespace trace