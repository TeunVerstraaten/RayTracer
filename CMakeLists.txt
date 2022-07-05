cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Werror -pedantic")
find_package(SDL2 REQUIRED)

add_executable(untitled main.cpp src/Ray.cpp src/Ray.h src/Sphere.cpp src/Sphere.h src/Global.h src/Plane.cpp src/Plane.h src/Hit.cpp src/Hit.h src/Scene.cpp src/Scene.h src/Identifier.cpp src/Identifier.h src/Types.h src/Material.cpp src/Material.h src/Disc.cpp src/Disc.h src/Eye.cpp src/Eye.h src/Math.cpp src/Math.h)
target_link_libraries(untitled SDL2)
