#ifndef PHYSICS_H
#define PHYSICS_H

#include "body.h"
#include "barneshuttree.h"
#include "vector3.h"

#include <cmath>
#include <vector>

namespace physics {
    enum class CollisionMode {
        Elastic,
        Inelastic,
        Collisionless
    };

    extern double dt;
    extern double G;

    void evolve(std::vector<Body*>& v, CollisionMode mode);
}

#endif