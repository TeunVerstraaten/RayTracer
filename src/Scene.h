//
// Created by pc on 11-12-21.
//

#ifndef _SCENE_H
#define _SCENE_H

#include "Disc.h"
#include "Plane.h"
#include "Sphere.h"

#include <vector>

namespace trace {

    struct Scene {
        Scene() = default;

        void                        randomizeSpheres();
        [[nodiscard]] const Sphere& sphereByIdentifier(size_t _identifier) const;

        std::vector<Sphere> spheres;
        std::vector<Plane>  planes;
        std::vector<Disc>   discLights;
        Sphere              light = Sphere{.0001, {27, -80, -12}, Material{}};
    };
} // namespace trace

#endif // _SCENE_H
