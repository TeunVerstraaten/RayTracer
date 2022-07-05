//
// Created by pc on 11-12-21.
//

#include "Scene.h"

#include <cstdlib>
#include <glm/geometric.hpp>
#include <string>

namespace trace {

    void Scene::randomizeSpheres() {
        for (auto& sphere : spheres) {
            sphere.center = {rand() % 34 - 8, rand() % 17 - 8, rand() % 9 + 12};

            size_t f = rand() % 3;
            if (f == 0)
                sphere.material = Material::preset(Material::PRESET::GLASS, {rand() % 255, rand() % 255, rand() % 255});
            else if (f == 1)
                sphere.material = Material::preset(Material::PRESET::MIRROR, {rand() % 255, rand() % 255, rand() % 255});
            else
                sphere.material = Material::preset(Material::PRESET::DULL, {rand() % 255, rand() % 255, rand() % 255});
        }
        // Make sure they do not intersect
        for (size_t i = 0; i != spheres.size(); ++i) {
            float minDistance = std::numeric_limits<float>::max();
            for (size_t j = 0; j != spheres.size(); ++j) {
                if (i == j)
                    continue;

                const float distance = glm::distance(spheres[i].center, spheres[j].center);
                if (distance < minDistance)
                    minDistance = distance;
            }
            spheres[i].radius = 0.45f * minDistance;
        }
    }

    const Sphere& Scene::sphereByIdentifier(size_t _identifier) const {
        for (const Sphere& sphere : spheres)
            if (sphere.identifier == _identifier)
                return sphere;

        //    assert(false);
        throw std::string("No sphers by this _identifier...");
    }
} // namespace trace