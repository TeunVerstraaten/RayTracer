#include "src/Eye.h"
#include "src/Global.h"
#include "src/Ray.h"
#include "src/Scene.h"
#include "src/Sphere.h"

#include <SDL2/SDL.h>
#include <chrono>
#include <glm/geometric.hpp>
#include <iostream>
#include <vector>

using namespace trace;

Scene buildScene() {
    Scene scene;
    scene.spheres = std::vector<Sphere>(65);
    scene.planes.push_back({{0, 0, 80}, {0, 0, -1}, Material::preset(Material::PRESET::DULL, {123, 152, 254})});
    scene.planes.push_back({{-30, 0, 0}, {1, 0, 0}, Material::preset(Material::PRESET::DULL, {199, 255, 9})});
    scene.planes.push_back({{30, 0, 0}, {-1, 0, 0}, Material::preset(Material::PRESET::DULL, {185, 145, 155})});
    scene.planes.push_back({{0, 30, 0}, {0, -1, 0}, Material::preset(Material::PRESET::DULL, {115, 16, 105})});
    scene.planes.push_back({{0, -30, 0}, {0, 1, 0}, Material::preset(Material::PRESET::DULL, {155, 123, 25})});
    scene.planes.push_back({{0, 0, -10}, {0, 0, 1}, Material::preset(Material::PRESET::DULL, {123, 52, 14})});
    scene.discLights.push_back({8, {-29, 0, 40}, {1, 0, 0}, Material::preset(Material::PRESET::DULL, {225, 225, 222})});
    scene.discLights.push_back({8, {29, 0, 40}, {-1, 0, 0}, Material::preset(Material::PRESET::DULL, {225, 225, 222})});
    scene.randomizeSpheres();
    return scene;
}

void updateScreen(const Scene& scene, SDL_Renderer* renderer) {
    for (size_t x = 0; x != WINDOW_SIZE; ++x) {
        std::cout << "x=" << x << "\n";
        for (size_t y = 0; y != WINDOW_SIZE; ++y) {
            glm::vec3 colour = {0, 0, 0};
            for (size_t i = 0; i != SAMPLES_PER_PIXEL; ++i)
                colour += Ray::rayFromPixel(static_cast<float>(x), static_cast<float>(y)).sampleColour(scene, MAX_DEPTH);

            const auto scale = 1.0f / static_cast<float>(SAMPLES_PER_PIXEL * 255);

            colour.x = 255 * glm::clamp(glm::sqrt(scale * colour.x), 0.f, 0.99f);
            colour.y = 255 * glm::clamp(glm::sqrt(scale * colour.y), 0.f, 0.99f);
            colour.z = 255 * glm::clamp(glm::sqrt(scale * colour.z), 0.f, 0.99f);
            SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

int main() {
    Scene scene = buildScene();

    SDL_Event     event;
    SDL_Renderer* renderer;
    SDL_Window*   window;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_SIZE, WINDOW_SIZE, 0, &window, &renderer);

    bool running     = true;
    bool needsUpdate = true;

    Eye eye;

    while (running) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
        }

        if (needsUpdate) {
            SDL_SetRenderDrawColor(renderer, 255, 91, 221, 0);
            SDL_RenderClear(renderer);

            auto start = std::chrono::high_resolution_clock::now();
            updateScreen(scene, renderer);
            auto stop     = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Time taken by function: " << duration.count() / 1000000.0f << " seconds" << std::endl;

            SDL_RenderPresent(renderer);
            needsUpdate = false;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
