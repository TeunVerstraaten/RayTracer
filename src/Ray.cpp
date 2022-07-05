//
// Created by pc on 11-12-21.
//

#include "Ray.h"

#include "Global.h"
#include "Hit.h"
#include "Math.h"
#include "Plane.h"
#include "Scene.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace trace {

    Ray::Ray(const glm::vec3& _start, const glm::vec3& _direction) : start(_start), direction(glm::normalize(_direction)) {
    }

    glm::vec3 Ray::sampleColour(const Scene& scene, size_t depth) const {
        if (depth == 0)
            return {0, 0, 0};

        const auto hitSphere = closestSphereHit(scene.spheres);
        const auto hitPlane  = closestPlaneHit(scene.planes);
        const auto hitLight  = closestLightHit(scene.discLights);

        const auto closestHit = std::min(hitSphere, std::min(hitPlane, hitLight));
        if (closestHit.distance !=
            std::numeric_limits<float>::max()) // Ray intersects something. This check may seem stupid, but whenever there is not
                                               // a hit we explicitly return std::numeric_limits<float>::max().
            return colourFromHit(closestHit, scene, depth);

        // Ray goes off into the background
        auto t = 255 * (direction.y + 1.0f);
        return (255.0f - t) * glm::vec3{1.0, 1.0, 1.0} + t * glm::vec3{0.5, 0.7, 1.0};
    }

    Ray Ray::rayFromPixel(float x, float y) {
        Ray        result;
        const auto scaledX = (2.0f * x) / WINDOW_SIZE - 1;
        const auto scaledY = (2.0f * y) / WINDOW_SIZE - 1;
        result.direction   = glm::normalize(glm::vec3{scaledX, scaledY, 1});
        return result;
    }

    Hit Ray::closestSphereHit(const std::vector<Sphere>& spheres) const {
        float  runningMinimumDistance = std::numeric_limits<float>::max();
        size_t runningIndexOfClosest  = std::numeric_limits<size_t>::max();
        for (size_t i = 0; i != spheres.size(); ++i) {
            const auto distance = spheres[i].distance(*this);
            if (distance >= DISTANCE_CUT_OFF)
                if (distance < runningMinimumDistance) {
                    runningMinimumDistance = distance;
                    runningIndexOfClosest  = i;
                }
        }
        if (runningIndexOfClosest == std::numeric_limits<size_t>::max())
            return {};

        const auto& sphere            = spheres[runningIndexOfClosest];
        const auto& intersectionPoint = start + runningMinimumDistance * direction;
        return {sphere.identifier,
                runningMinimumDistance,
                OBJECT_TYPE::SPHERE,
                sphere.material,
                intersectionPoint,
                glm::normalize(glm::vec3(intersectionPoint - sphere.center) / sphere.radius),
                direction};
    }

    Hit Ray::closestLightHit(const std::vector<Disc>& discs) const {
        float  runningMinimumDistance = std::numeric_limits<float>::max();
        size_t runningIndexOfClosest  = std::numeric_limits<size_t>::max();
        for (size_t i = 0; i != discs.size(); ++i) {
            const auto distance = discs[i].distance(*this);
            if (distance >= DISTANCE_CUT_OFF)
                if (distance < runningMinimumDistance) {
                    runningMinimumDistance = distance;
                    runningIndexOfClosest  = i;
                }
        }
        if (runningIndexOfClosest == std::numeric_limits<size_t>::max())
            return {};

        const auto& disc = discs[runningIndexOfClosest];
        return {disc.identifier, runningMinimumDistance, OBJECT_TYPE::LIGHT, disc.material};
    }

    Hit Ray::closestPlaneHit(const std::vector<Plane>& planes) const {
        float  runningMinimumDistance = std::numeric_limits<float>::max();
        size_t runningIndexOfClosest  = std::numeric_limits<size_t>::max();
        for (size_t i = 0; i != planes.size(); ++i) {
            const auto distance = planes[i].distance(*this);
            if (distance >= DISTANCE_CUT_OFF)
                if (distance < runningMinimumDistance) {
                    runningMinimumDistance = distance;
                    runningIndexOfClosest  = i;
                }
        }

        if (runningIndexOfClosest == std::numeric_limits<size_t>::max())
            return {};

        const auto& plane = planes[runningIndexOfClosest];
        return {plane.identifier,
                runningMinimumDistance,
                OBJECT_TYPE::PLANE,
                plane.material,
                start + runningMinimumDistance * direction,
                plane.normal,
                direction};
    }

    glm::vec3 Ray::colourFromHit(const Hit& hit, const Scene& scene, size_t depth) {
        if (hit.type == OBJECT_TYPE::LIGHT)
            return hit.material.color;

        const auto& material        = hit.material;
        glm::vec3   resultantColour = {0, 0, 0};

        // Ambient
        if (hit.type == OBJECT_TYPE::SPHERE)
            resultantColour +=
                material.ambientFactor *
                (0.8f * material.color + 255.0f * 0.1f * (glm::normalize(hit.outwardNormal) + glm::vec3{1.0, 1.0, 1.0}));
        else
            resultantColour += material.ambientFactor * material.color;

        // Diffuse
        if (material.diffuseFactor >= 0.001)
            resultantColour +=
                material.diffuseFactor *
                Ray{hit.intersectionPoint, material.diffuseExponent * hit.outwardNormal + math::randomOnUnitSphere()}
                    .sampleColour(scene, depth - 1);

        // Reflection
        const auto reflectedDirection =
            hit.inwardDirection - 2.f * glm::dot(hit.inwardDirection, hit.outwardNormal) * hit.outwardNormal;
        if (material.reflectionCoefficient >= 0.001) {
            const auto reflectedRay = Ray{hit.intersectionPoint, reflectedDirection + material.fuzz * math::randomOnUnitSphere()};
            resultantColour += material.reflectionCoefficient * reflectedRay.sampleColour(scene, depth - 1);
        }

        // Refraction
        if (material.refractionCoefficient >= 0.001)
            resultantColour += material.refractionCoefficient * refractedColourFromHit(hit, scene, depth);

        return resultantColour;
    }

    Ray refract(const Ray& ray, const glm::vec3& outwardNormal, float n1, float n2) {
        const float phiIn = glm::angle(ray.direction, -outwardNormal);
        if (phiIn > glm::pi<float>() - 0.01f)
            return ray;

        const float sinPhiOut = (n1 / n2) * glm::sin(phiIn);
        if (sinPhiOut >= 1.0)
            return {{0, 0, 0}, {0, 0, 0}};

        const float phiOut = glm::asin(sinPhiOut) / phiIn;
        const auto  refractedDirection =
            glm::normalize(glm::rotate(outwardNormal, phiOut, glm::cross(ray.direction, outwardNormal)));
        return Ray{ray.start + 0.01f * refractedDirection, refractedDirection};
    }

    glm::vec3 Ray::refractedColourFromHit(const Hit& hit, const Scene& scene, size_t depth) {
        auto refractedRay = refract({hit.intersectionPoint, hit.inwardDirection},
                                    -hit.outwardNormal - hit.material.fuzz * math::randomOnUnitSphere(),
                                    0.94,
                                    1.0);
        if (refractedRay.direction == glm::vec3{0, 0, 0})
            return Ray{hit.intersectionPoint + 0.001f * hit.inwardDirection, hit.inwardDirection}.sampleColour(scene, depth);

        const auto& sphere = scene.sphereByIdentifier(hit.identifier);
        const auto  d      = sphere.distance(refractedRay);
        if (d == 0 || d == std::numeric_limits<float>::max())
            return Ray{hit.intersectionPoint + 0.001f * hit.inwardDirection, hit.inwardDirection}.sampleColour(scene, depth);

        refractedRay.start += d * refractedRay.direction;
        return refract(refractedRay, sphere.center - refractedRay.start, 1.0, 0.94).sampleColour(scene, depth - 1);
    }
} // namespace trace