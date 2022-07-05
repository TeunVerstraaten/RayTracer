//
// Created by pc on 11-12-21.
//

#ifndef _RAY_H
#define _RAY_H

#include "Hit.h"

#include <glm/vec3.hpp>
#include <vector>

namespace trace {

    struct Scene;
    struct Sphere;
    struct Plane;
    struct Disc;

    struct Ray {
        Ray() = default;
        Ray(const glm::vec3& _start, const glm::vec3& _direction);

        // The following three functions should probably be moved out of this class
        [[nodiscard]] Hit       closestSphereHit(const std::vector<Sphere>& spheres) const;
        [[nodiscard]] Hit       closestPlaneHit(const std::vector<Plane>& planes) const;
        [[nodiscard]] Hit       closestLightHit(const std::vector<Disc>& discs) const;
        [[nodiscard]] glm::vec3 sampleColour(const Scene& scene, size_t depth) const;

        [[nodiscard]] static glm::vec3 colourFromHit(const Hit& hit, const Scene& scene, size_t depth);
        [[nodiscard]] static glm::vec3 refractedColourFromHit(const Hit& hit, const Scene& scene, size_t depth);
        [[nodiscard]] static Ray       rayFromPixel(float x, float y);

        glm::vec3 start     = glm::vec3(0, 0, 0);
        glm::vec3 direction = glm::vec3(0, 0, 0);
    };
} // namespace trace

#endif // _RAY_H
