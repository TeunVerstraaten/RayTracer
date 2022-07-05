//
// Created by pc on 11-12-21.
//

#include "Disc.h"

#include "Global.h"
#include "Ray.h"

#include <glm/geometric.hpp>

namespace trace {

    Disc::Disc(float _radius, const glm::vec3& _center, const glm::vec3& _normal, const Material& _material)
        : Identifier(),
          radius(_radius),
          dotNormalCenter(-glm::dot(_normal, _center)),
          center(_center),
          normal(_normal),
          material(_material) {
    }

    float Disc::distance(const Ray& _ray) const {
        const auto normalDot = glm::dot(normal, _ray.direction);
        if (normalDot == 0) // Ray is parallel to disc surface
            return std::numeric_limits<float>::max();

        const auto dist = -(glm::dot(normal, _ray.start) + dotNormalCenter) / normalDot;
        if (dist < DISTANCE_CUT_OFF) // We don't want hits that are too close, to prevent bouncing rays from immediately colliding
                                     // with the same object
            return std::numeric_limits<float>::max();

        const auto hit = _ray.start + dist * _ray.direction;
        if (glm::distance(hit, center) > radius)
            return std::numeric_limits<float>::max();

        return dist;
    }
} // namespace trace