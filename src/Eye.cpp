//
// Created by pc on 11-12-21.
//

#include "Eye.h"

namespace trace {

    Eye::Eye() {
        auto aspect_ratio    = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width  = aspect_ratio * viewport_height;
        auto focal_length    = 1.0;

        origin            = glm::vec3(0, 0, 0);
        horizontal        = glm::vec3(viewport_width, 0.0, 0.0);
        vertical          = glm::vec3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0, 0, focal_length);
    }
} // namespace trace