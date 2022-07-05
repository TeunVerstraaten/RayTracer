//
// Created by pc on 11-12-21.
//

#ifndef _MATH_HEADER_GUARD
#define _MATH_HEADER_GUARD

#include <glm/vec3.hpp>

namespace trace {

    namespace math {

        float     random_double();
        float     random_double(float _min, float _max);
        glm::vec3 randomVec3(float _min, float _max);
        glm::vec3 randomOnUnitSphere();
    } // namespace math

} // namespace trace

#endif // _MATH_HEADER_GUARD
