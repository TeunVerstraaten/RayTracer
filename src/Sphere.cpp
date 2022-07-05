//
// Created by pc on 11-12-21.
//

#include "Sphere.h"

#include "Ray.h"

#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>

namespace trace {

    static float square(float a) {
        return a * a;
    }

    Sphere::Sphere() : Identifier() {
    }

    Sphere::Sphere(const Sphere& _other) : Identifier(), radius(_other.radius), center(_other.center), material(_other.material) {
    }

    Sphere::Sphere(float _radius, const glm::vec3& _center, const Material& _material)
        : Identifier(), radius(_radius), center(_center), material(_material) {
    }

    float Sphere::distance(const Ray& _ray) const {
        const auto v = _ray.start - center;
        const auto d = square(glm::dot(v, _ray.direction)) + square(radius) - glm::dot(v, v);
        if (d <= 0) {
            return std::numeric_limits<float>::max();
        }
        return -glm::dot(v, _ray.direction) - std::sqrt(d);
    }
} // namespace trace
