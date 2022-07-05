//
// Created by pc on 11-12-21.
//

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <glm/vec3.hpp>

namespace trace {

    struct Material {
        enum class PRESET { GLASS, DULL, MIRROR };

        static Material preset(PRESET _type, const glm::vec3& _ambientColor);

        Material() = default;

        Material(float            _ambientFactor,
                 float            _diffuseFactor,
                 float            _diffuseExponent,
                 float            _reflectionCoefficient,
                 float            _refractionCoefficient,
                 float            _fuzz,
                 const glm::vec3& _ambientColor);

        float     ambientFactor;
        float     diffuseFactor;
        float     diffuseExponent;
        float     reflectionCoefficient;
        float     refractionCoefficient;
        float     fuzz;
        glm::vec3 color;
    };
} // namespace trace

#endif // _MATERIAL_H
