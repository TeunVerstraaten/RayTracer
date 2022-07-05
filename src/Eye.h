//
// Created by pc on 11-12-21.
//

#ifndef _EYE_H
#define _EYE_H

#include <glm/vec3.hpp>

namespace trace {

    struct Eye {
        Eye();

        glm::vec3 origin{};
        glm::vec3 lower_left_corner{};
        glm::vec3 horizontal{};
        glm::vec3 vertical{};
    };

} // namespace trace

#endif // _EYE_H
