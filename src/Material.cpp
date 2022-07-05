//
// Created by pc on 11-12-21.
//

#include "Material.h"

namespace trace {

    Material::Material(float            _ambientFactor,
                       float            _diffuseFactor,
                       float            _diffuseExponent,
                       float            _reflectionCoefficient,
                       float            _refractionCoefficient,
                       float            _fuzz,
                       const glm::vec3& _ambientColor)
        : ambientFactor(_ambientFactor),
          diffuseFactor(_diffuseFactor),
          diffuseExponent(_diffuseExponent),
          reflectionCoefficient(_reflectionCoefficient),
          refractionCoefficient(_refractionCoefficient),
          fuzz(_fuzz),
          color(_ambientColor) {
    }

    Material Material::preset(Material::PRESET _type, const glm::vec3& _ambientColor) {
        switch (_type) {
            case PRESET::GLASS:
                return Material{0.04, 0.0, 1.0, 0.0, 0.9, 0.01, _ambientColor};
            case PRESET::MIRROR:
                return Material{0.1, 0.2, 0.5, 0.7, 0.0, 0.02, _ambientColor};
            case PRESET::DULL:
                return Material{0.5, 0.5, 1.8, 0.0, 0.0, 0, _ambientColor};
        }
        return Material{};
    }
} // namespace trace